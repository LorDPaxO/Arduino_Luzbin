#include <Wire.h>
#include <SPI.h>

#define selector 6
#define PWM_pin 5

const int slaveSelectPin_DDS1 = 14;

  //* CS - to digital pin 10  (SS pin)
  //* SDI - to digital pin 11 (MOSI pin)
  //* CLK - to digital pin 13 (SCK pin)

#define SPI_CLOCK_SPEED      12000000

// Variable de tipo de corte
int tipo_corte=1;


void setup() {

  Wire.begin(7);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  pinMode(selector,OUTPUT);
  digitalWrite(selector,HIGH);
  
  // MODIFICAR LA FRECUENCIA DEL PWM DEL PIN 9 (PIN DIGITAL 5 DE ARDUINO)
  //TCCR0B = _BV(CS00);             // Frecuencia de 31372 Hz para el pin PWM
  TCCR0B = _BV(CS01);             // Frecuencia de 3921 Hz para el pin PWM
  //TCCR0B = _BV(CS00) | _BV(CS01); // Frecuencia de 490 Hz para el pin PWM, Valor por defecto en el Microprocesador
  //TCCR0B = _BV(CS02);             // Frecuencia de 122 Hz para el pin PWM
  //TCCR0B = _BV(CS00) | _BV(CS02); // Frecuencia de 30 Hz para el pin PWM
  
  pinMode(slaveSelectPin_DDS1,OUTPUT);
  // initialize SPI:
  SPI.begin();
  delay(10);
  for (int hola = 1; hola < 10; hola++) {
    SET_DDS_1();
    delay(20);
    }
  Serial.begin(9600);
}

void loop() {

  
}

  void receiveEvent(int howMany) {
    tipo_corte = Wire.read();
    SELECCION_MUX();
    //delay(10);
  }


void SET_DDS_1() {

  // take the SS pin low to select the chip:
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE2));   
  
  digitalWrite(slaveSelectPin_DDS1, LOW);
  //  send in the address and value via SPI:
  
  SPI.transfer16(0x2128); //Trama de configuración y activación del reset
  SPI.transfer16(0x6707); //01 + dato de frecuencia que son 14 bits los menos significativos
  SPI.transfer16(0x40C4); //01 + dato de frecuencia que son 14 bits los mas significativos
  SPI.transfer16(0xC000); //Fase, No mover se va a dejar en cero, en este caso no importa =)
  SPI.transfer16(0x2028); //Trama de configuración y desactivación del reset
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin_DDS1, HIGH);
  SPI.endTransaction();
}

void SELECCION_MUX(){

    //Tener en cuenta sentido del multiplexor, verificar en laboratorio.
    switch (tipo_corte) {
      
    case 1:    // Corte puro
      analogWrite(PWM_pin,255);
      digitalWrite(selector,LOW); 
      break;
      
    case 2:    // Corte Mixto
      analogWrite(PWM_pin,230);
      digitalWrite(selector,LOW); 
      break;
      
    case 3:    // Corte MinDo
      analogWrite(PWM_pin,255);
      digitalWrite(selector,HIGH);
      break;
      
    case 4:    // Coag Alto
      analogWrite(PWM_pin,160);
      digitalWrite(selector,LOW); 
      break;
      
    case 5:    // Coag Medio
      analogWrite(PWM_pin,140);
      digitalWrite(selector,LOW); 
      break;
      
    case 6:    // Coag Bajo
      analogWrite(PWM_pin,120);
      digitalWrite(selector,LOW); 
      break;
      
      default:{
        //Si llega un dato erroneo o no llega nada se pone corte puro.
        analogWrite(PWM_pin,255);
        digitalWrite(selector,LOW);         
        }
  }

  // Cambiar por lo que necesitoESTADO = Wire.read();    // receive byte as an integer
  //Serial.println(ESTADO);
}


