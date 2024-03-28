#include <math.h>
#include <EEPROM.h>

#define ARRAY_SIZE 512
#define DEGREES 360
#define EEPROM_START_ADDR 0 //Start adress in EEPROM


// unsigned long results[ARRAY_SIZE] = {0};
// float cos_result[DEGREES] = {0.0};
unsigned long result = 0;

//Returns twice the square of the passed value
unsigned long twice_square(unsigned long value){
  return value*value*2;
}

// unsigned long = 4 bytes, EEPROM = 1024 bytes total storage, 1024/4 = 256, so we 256 elements, but an array size of 512

void setup() {
  Serial.begin(9600);

  for(int i = 0; i<ARRAY_SIZE;i++){
    result = twice_square(i);
    EEPROM.put(EEPROM_START_ADDR + i*sizeof(unsigned long), result);
  }

  for(int i=0;i<ARRAY_SIZE;i++){
    EEPROM.get(EEPROM_START_ADDR + i*sizeof(unsigned long), result);
    Serial.print(i);
    Serial.print(":");
    Serial.println(result);
  }

  // for(int i = 0;i<=DEGREES;i++){
  //   Serial.print("cos(");
  //   Serial.print(i);
  //   Serial.print("):");
  //   Serial.println(cos(i));
  // }
}

void loop() {
  
}


