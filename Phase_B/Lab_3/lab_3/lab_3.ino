#define GREEN_LED 4
#define RED_LED   5
#define BUTTON_1  2

#define TIMER1_COMPARE_VALUE 6250
#define TIMER2_COMPARE_VALUE

int gCounter = 0;
bool gPrint = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_1, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  configureTimers();
}

void loop() {
  if(gPrint){
    Serial.print("Counter: ");
    Serial.println(gCounter/10);
    gPrint = false;
  }
}

void configureTimers(){
  noInterrupts();

  //Timer/Counter 1 Control Register A/B
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR2A = 0;
  TCCR2B = 0;

  //Output Compare registers
  OCR1A = TIMER1_COMPARE_VALUE;
  OCR2A = TIMER2_COMPARE_VALUE;

  //Config settings for timer
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12);

  TCCR2A |= (1<<WGM11);
  TCCR2B |= (1<<CS21);


  //enable interrupts from output compare registers A and B
  TIMSK1 |= (1<<OCIE1A);
  interrupts();
}

//Interrupt
ISR(TIMER1_COMPA_vect){
  gCounter++;
  digitalWrite(RED_LED, digitalRead(BUTTON_1));
  if(gCounter%10 == 0){
    digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
  }
  if(gCounter%30 == 0){
    gPrint = true;
  }
}



