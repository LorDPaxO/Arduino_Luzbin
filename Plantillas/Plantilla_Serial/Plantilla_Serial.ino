
char message[8] = "hello";
char mensaje_Prueba = "Hola";
void setup() {

  Serial.begin(9600);
  

}

void loop() {

  //saludos();
  message[1]= 'z';
  Serial.println(message);
  Serial.println(mensaje_Prueba);
  delay(200);
  message[4]='L';

}

/*
void saludos(){

  while(Serial.available()){
    char mensaje = Serial.read();
    Serial.println(mensaje);
    delay(500);
    if(mensaje == "hola"){
        Serial.println("Hola Luzbin, Estamos Bien");
        delay(2000);
      }
        
    }
  
  }
*/
