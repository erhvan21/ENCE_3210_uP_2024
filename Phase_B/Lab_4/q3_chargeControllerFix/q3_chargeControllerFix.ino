#define RED_LED 8  // SP -> uP
#define BLUE_LED 7 // SP -> Battery
#define GREEN_LED 4// Battery -> uP

#define SOLAR_PIN A0
#define BATT_PIN A1


#define VREF 2.5
#define VBATT 6

enum STATE {SOLAR, BATT, CHARGE};
char gState = SOLAR;

float solarVolt = 0;
float battVolt = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(SOLAR_PIN, INPUT);
  pinMode(BATT_PIN, INPUT);

}

void loop() {
  // read inputs
  battVolt = analogRead(BATT_PIN);
  solarVolt = analogRead(SOLAR_PIN);

  // state control logic
  switch(gState){
    case SOLAR:
      digitalWrite(RED_LED,HIGH);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED,LOW);
      if(solarVolt<VREF){
        gState = BATT;
      }
      break;
    case BATT:
      digitalWrite(RED_LED,LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(GREEN_LED,HIGH);
      if(solarVolt>=VREF){
        gState = SOLAR;
      }
      else if(solarVolt > battVolt){
        gState = CHARGE;
      }
      break;
    case CHARGE:
      digitalWrite(RED_LED,LOW);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(GREEN_LED,LOW);
      if(battVolt>VBATT){
        gState = SOLAR;
      }
  }
}
