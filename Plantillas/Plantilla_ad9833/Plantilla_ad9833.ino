
#include <SPI.h>

const int slaveSelectPin = 10;       // Comando para escribir en el AD5933 

  //* CS - to digital pin 10  (SS pin)
  //* SDI - to digital pin 11 (MOSI pin)
  //* CLK - to digital pin 13 (SCK pin)

#define SPI_CLOCK_SPEED      12000000

#define this_pin 5
void setup() {
  pinMode(this_pin,OUTPUT);
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  delay(10);
  for (int hola = 1; hola < 10; hola++) {
    SET_AD9833();
    delay(20);
    }
  Serial.begin(9600);
}

void loop() {
  
}

void SET_AD9833() {
  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2));   
  
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  
  SPI.transfer16(0x2128);//2128
  SPI.transfer16(0x69F1); //01 + dato de frecuencia que son 14 bits
  //SPI.transfer16(0x50C7); //01 + el resto del dato de frecuencia
  SPI.transfer16(0x4000); //Fase, No mover
  SPI.transfer16(0xC000); //Fase, No mover 
  SPI.transfer16(0x2028);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
  SPI.endTransaction();
}

//0010 0000 0010 0000
//0010 0000 0000 0010

//00010 0001 0010 0010
