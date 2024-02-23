#define GREEN_LED 4
#define RED_LED   5
#define BUTTON_1  2

#define TIMER1_COMPARE_VALUE 25000

volatile int gCounter = 0;
bool gPrint = false;

void setup() {
  Serial.begin(9600);
  configurePins();
  configureTimers();
}

void loop() {
  //Main task, prints to serial
  if(gPrint){
    Serial.print("Counter: ");
    Serial.println(gCounter/10);
    gPrint = false;
  }
}

//contains setup for timers
void configureTimers(){
  //Turn off interrupts
  noInterrupts();

  //reset Timer/Counter 1 Control Register A/B
  TCCR1A = 0;
  TCCR1B = 0;

  //set Output Compare register value
  OCR1A = TIMER1_COMPARE_VALUE;

  //Config settings for timer
  TCCR1B |= (1<<WGM12); //CTC mode
  TCCR1B |= (1<<CS11); //64 prescalar
  TCCR1B |= (1<<CS10);

  //enable interrupts from output compare registers A and B
  TIMSK1 |= (1<<OCIE1A);
  interrupts();
}

//contains setup for pins
void configurePins(){
  pinMode(BUTTON_1, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

//Interrupt, 10 Hz
ISR(TIMER1_COMPA_vect){

  //Task 2, write to RED_LED
  digitalWrite(RED_LED, digitalRead(BUTTON_1));
  gCounter++;

  //Task 1, 1 Hz, toggle GREEN_LED
  if(gCounter%10 == 0){
    digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
  }

  //Main task, 0.333 Hz, raise print flag
  if(gCounter%30 == 0){
    gPrint = true;
  }
}



