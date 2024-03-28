#include <SPI.h>

#define CS 10

//MAX7219CNG Control Registers (THE LED Matrix)
#define DECODE_MODE 0x09
#define INTENSITY 0x0A
#define SCAN_LIMIT 0x0B
#define SHUTDOWN 0x0C
#define DISPLAY_TEST 0x0F

// MISO to DIN
// MOSI to CS
// SCK to CLK

const uint8_t NUMS[][8] = {
{
  0b00111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100
},{
  0b00011000,
  0b00011000,
  0b01111000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00111100,
  0b01111110
},{
  0b00111100,
  0b01111110,
  0b01000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b01111110,
  0b01111110
},{
  0b00111100,
  0b01111110,
  0b00000010,
  0b00111110,
  0b00111110,
  0b00000010,
  0b01111110,
  0b00111100
},{
  0b00001100,
  0b00011100,
  0b00110100,
  0b01100110,
  0b01111110,
  0b00001100,
  0b00001100,
  0b00001100
},{
  0b01111110,
  0b01111110,
  0b01100000,
  0b01111100,
  0b00001110,
  0b00000110,
  0b01111110,
  0b00111100
},{
  0b00111100,
  0b01111110,
  0b01100000,
  0b01111100,
  0b01100110,
  0b01100110,
  0b01100110,
  0b00111100
},{
  0b00000000,
  0b01111110,
  0b01111110,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00110000,
  0b01100000
},{
  0b00111100,
  0b01100110,
  0b01100110,
  0b00111100,
  0b00111100,
  0b01100110,
  0b01100110,
  0b00111100
},{
  0b00111100,
  0b01100110,
  0b01000010,
  0b01100110,
  0b00111110,
  0b00000110,
  0b01111110,
  0b00111100
}};
const int NUMS_LEN = sizeof(NUMS)/8;



void setup(){
    //initialize SPI pins
    pinMode(CS,OUTPUT);
    SPI.begin();
}

void loop(){
    writeRegister(DISPLAY_TEST,0x01); // turns on all the LEDs
    delay(1000);
    writeRegister(DISPLAY_TEST,0x00); // returns to normal operation
    writeRegister(SHUTDOWN,0x00);
}

void writeRegister(uint8_t reg, uint8_t data){
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW); // Start transfer

    SPI.transfer(reg);
    SPI.transfer(data);

    digitalWrite(CS,HIGH); // End transfer
    SPI.endTransaction();
}