
#include <Wire.h>
#define this_pin 13
//int estado = 0;
int prueba = 0;
char estado;
void setup() {

	Wire.begin();//INICIAMOS EL WIRE (I2C)
	Serial.begin(9600);// INICIAMOS EL SERIAL PARA MOSTRAR LOS MENSAJES
  pinMode(this_pin,OUTPUT);
}

void loop() {


  Serial.print(prueba);//IMPRIMIMOS EL MENSAJE
  
  Wire.requestFrom(1,2);//REALIZAMOS UNA PETICION AL CANAL 1 DE 1 BYTE

  while(Wire.available())
  { 
   estado = Wire.read();//GUARDAMOS EL MENSAJE EN LA CADENA MESAJE 1   
   Serial.print(estado);//IMPRIMIMOS EL MENSAJE
   delay(100); 
  }

}
