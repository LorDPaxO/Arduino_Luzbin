
#include <SPI.h>

const int slaveSelectPin = 10;       // Comando para escribir en el AD5933 

  //* CS - to digital pin 10  (SS pin)
  //* SDI - to digital pin 11 (MOSI pin)
  //* CLK - to digital pin 13 (SCK pin)

#define SPI_CLOCK_SPEED      12000000

void setup() {
  
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  SET_AD9833();
  delay(10);
  Serial.begin(9600);
}

void loop() {

  

}


void SET_AD9833() {
  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2)); 
  //dataOrder: MSBFIRST or LSBFIRST
  //dataMode : SPI_MODE0, SPI_MODE1, SPI_MODE2, or SPI_MODE3
  
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer16(0x21F0);
  SPI.transfer16(0x50C7);
  SPI.transfer16(0x4FF0);
  SPI.transfer16(0xCFF0);
  SPI.transfer16(0x2000);

  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
}

/*
void setWave() {
  long freq_data = frequency * pow(2, 28) / REF_FREQ;
  int freq_MSB = (int)(freq_data >> 14) | FREQ0;
  int freq_LSB = (int)(freq_data & 0x3FFF) | FREQ0;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2));
  digitalWrite(SS, LOW);

  SPI.transfer16(CR_B28_COMBINED | CR_FSELECT_0 | CR_PSELECT_0 | CR_RESET);
  SPI.transfer16(freq_LSB);
  SPI.transfer16(freq_MSB);
  SPI.transfer16(PHASE0);
  SPI.transfer16(waveform);

  digitalWrite(SS, HIGH);
  SPI.endTransaction();
}
*/
