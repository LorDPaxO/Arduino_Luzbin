
#include <SPI.h>
#define PWM_pin 6

const int slaveSelectPin_DDS1 = 10;       // Comando para escribir en el AD5933 
const int slaveSelectPin_DDS2 = 9;       // Comando para escribir en el AD5933 

  //* CS - to digital pin 10  (SS pin)
  //* SDI - to digital pin 11 (MOSI pin)
  //* CLK - to digital pin 13 (SCK pin)

#define SPI_CLOCK_SPEED      12000000

#define this_pin 5
void setup() {
  TCCR0B = _BV(CS01);
  pinMode(slaveSelectPin_DDS1,OUTPUT);
  pinMode(slaveSelectPin_DDS2, OUTPUT);
  // initialize SPI:
  SPI.begin();
  delay(10);
  for (int hola = 1; hola < 10; hola++) {
    SET_DDS_1();
    delay(20);
    SET_DDS_2();
    delay(20);
    
    }
  Serial.begin(9600);
}

void loop() {
  analogWrite(PWM_pin,128);
}



void SET_DDS_1() {

  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2));   
  
  digitalWrite(slaveSelectPin_DDS1, LOW);
  //  send in the address and value via SPI:
  
  SPI.transfer16(0x2128); //Trama de configuración y activación del reset
  SPI.transfer16(0x4000); //01 + dato de frecuencia que son 14 bits los menos significativos
  SPI.transfer16(0x4041); //01 + dato de frecuencia que son 14 bits los mas significativos
  SPI.transfer16(0xC000); //Fase, No mover se va a dejar en cero, en este caso no importa =)
  SPI.transfer16(0x2028); //Trama de configuración y desactivación del reset
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin_DDS1, HIGH);
  SPI.endTransaction();
}

void SET_DDS_2() {

  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2));   
  
  digitalWrite(slaveSelectPin_DDS2, LOW);
  //  send in the address and value via SPI:
  
  SPI.transfer16(0x2128); //Trama de configuración y activación del reset
  SPI.transfer16(0x67C5); //01 + dato de frecuencia que son 14 bits los menos significativos
  SPI.transfer16(0x4002); //01 + dato de frecuencia que son 14 bits los mas significativos
  SPI.transfer16(0xC000); //Fase, No mover se va a dejar en cero, en este caso no importa =)
  SPI.transfer16(0x2028); //Trama de configuración y desactivación del reset
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin_DDS2, HIGH);
  SPI.endTransaction();
}

