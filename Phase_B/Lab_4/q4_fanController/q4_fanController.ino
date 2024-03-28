#define TEMP_PIN A0
#define FAN_PIN A1
#define BUTTON_1 2
#define BUTTON_2 3

#define RED_LED 8   // speed 0
#define BLUE_LED 7  // speed 1
#define GREEN_LED 4 // speed 2

#define TIMER_2_COMP_VAL 78
#define ICR1_TOP 64000

#define debug false
#define bitsize 14

#define numSamples 100
#define averagePeriod 5
int gSampleCounter = 0;

int gFanSpeed = 0;
bool gFanState = true;

bool gAverageBool = false;
float gAverageTemp = 0;


struct BinaryQuantized{
  int binary[bitsize] = {0};
  float quantized = 0.0;
};


void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isrOnOff, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isrSpeed, RISING);

  noInterrupts();

  //Timer 1 - for making fan PWM
  // clear the control registers
  TCCR1A = 0;
  TCCR1B = 0;
  // reset the timer
  TCNT1 = 0;
  ICR1 - ICR1_TOP;
  // set the mode to fast pwm
  TCCR1A |= (1<<WGM11);
  TCCR1B |= (1<<WGM12) | (1<<WGM13);
  // set the compare output modes
  TCCR1A |= (1<<COM1A1) | (1<<COM1B1);
  // set the prescale to 1
  TCCR1B |= (1<<CS10);
  
  // Timer 2 - for counting samples
  // Speed = 16 MHz / 1024
  //reset control registers
  TCCR2A = 0;
  TCCR2B = 0;
  //set output compare register value
  OCR2A = TIMER_2_COMP_VAL;
  // set mode to CTC
  TCCR2A |= (1<<WGM21);
  // set timer prescalar
  TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);  //1024
  TIMSK2 |= (1<<OCIE2A); //enable interrupt from compare register 2A

  interrupts();

  isrSpeed();


}

void loop() {
  if(gAverageBool){
    gAverageBool = false;
    Serial.print("Average Temperature: ");
    Serial.println(gAverageTemp);
    gAverageTemp = 0;
  }
}

// controls the fan on/off button
void isrOnOff(){
  gFanState = ~gFanState;
  if(gFanState){
    isrSpeed();
  }
  else{

  }
}

// controls the fan speed logic and PWM
void isrSpeed(){
  if(gFanState){
    switch(gFanSpeed){
      case 0:
        gFanSpeed = 1;
        digitalWrite(RED_LED,HIGH);
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(GREEN_LED,LOW);
        break;
      case 1:
        gFanSpeed = 2;
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(GREEN_LED,LOW);
        break;
      case 2:
        gFanSpeed = 0;
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(GREEN_LED,HIGH);
        break;


    }


  }
}

//timer 2 interrupt for collecting samples every 5 ms
ISR(TIMER2_COMPA_vect){
  gSampleCounter++;
  gAverageTemp += analogRead(TEMP_PIN);
  if(gSampleCounter == numSamples){
    gSampleCounter = 0;
    gAverageBool = true;
    gAverageTemp /= numSamples;
  }
}

// SAR 14 converter function
BinaryQuantized SAR14(float Vin, float Vref){
  // function variables
  float thresh;             // fluctuating threshold 
  int bitval;               // changing bit value
  BinaryQuantized result;   // data to hold result
  float quantVal;           // changing quantized value

    // initial halfing, setting thresh to Vref
    Vref /= 2;
    thresh = Vref;

    // starting with MSB, for each bit in the output
    for(int count=0; count<bitsize; count++){
      // set the quantized value
      quantVal = Vref;
      // 1/2 the reference voltage
      Vref /= 2;
        // if thresh is greater than vin, lower threshold by vref, set bitval to 0
        if (thresh > Vin){
            bitval = 0;             // set bitVal to 0
            thresh -= Vref;         // subtract thresh from Vref
        }
        // if thresh is less than vin, raise threshold by vref, set bitval to 1
        else{
            bitval = 1;             // set bitVal to 1
            thresh += Vref;         // add Vref to thresh
        }
        result.binary[count] = bitval;       // set the bitVal in bits[count]
        if(bitval==1){
          result.quantized += quantVal;   // approximate what the quantized value would be
        }
    }
    return result;
}
