#define RED_LED   // SP -> uP
#define BLUE_LED  // SP -> Battery
#define GREEN_LED // Battery -> uP

#define SOLAR_PIN
#define BATT_PIN


#define VREF 2.5

float solarVolt = 0;
float battVolt = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  pinMode(SOLAR_PIN, INPUT);
  pinMode(BATT_PIN,INPUT);

}

void loop() {
  // read inputs
  battVolt = analogRead(BATT_PIN);
  solarVolt = analogRead(SOLAR_PIN);

  // control logic
  if(solarVolt>VREF){ // solar panel to uP, when solar is High
    digitalWrite(RED_LED,HIGH);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED,LOW);
  }
  else{ // when solar is low
    if(battVolt<solarVolt){ // solar panel to batt
    digitalWrite(RED_LED,LOW);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED,LOW);
    }
    else{ //if batt can supply voltage to uP, batt to uP
    digitalWrite(RED_LED,LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED,HIGH);
    }
  }

}
