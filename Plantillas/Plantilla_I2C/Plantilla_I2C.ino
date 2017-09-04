
#include <Wire.h>

//#define Slave_Add 0x01

//Voy a intentar enviar un entero
byte estado = 14;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(1); // Abrimos el canal 1 (0x01) del I2C
  Wire.onRequest(peticion); // Creamos el evento que se relaizará cuando el Receptor llame a el emisor (Este Arduino)
}

void loop() {
  
  // put your main code here, to run repeatedly:
  

}


void peticion(){
  //Wire.write("0"); //Envio el valor de estado
  while(Wire.available())
  { 
   //mensaje1 = Wire.read();//GUARDAMOS EL MENSAJE EN LA CADENA MESAJE 1   
   hola = Wire.read();
   Serial.println(hola);//IMPRIMIMOS EL MENSAJE
   delay(100); 
  }
  
  //Wire.write(estado);
}

//rEVISAR oNrQUEST

/*
  Wire.beginTransmission(Slave_Add);  // Envia los 7 bits de direccion del AD5933 + el bit de escritura (0), para comenzar
  Wire.write(Data_1);
  Wire.write(Data_2);
  Wire.endTransmission();
*/
