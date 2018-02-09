
#include <Wire.h> //INCLUYO LIBRERÍA PARA USAR I2C

//FALTA BORRAR EL DEBUGGER QUE TENGO CON COMUNICACIÓN RS232


//DEFINICION DE ESTADOS
#define INICIO 0
#define MONITOREAR_PLACA 1
#define CORTE_FAIL 2
#define MONITOREAR_Z 3
#define ELECCION_MODO 4
#define CORTAR 5
#define COAGULAR 6


//DEFINICIÓN DE SALIDAS DE LA TARJETA QUE GESTIONA LOS PINES DE LA MÁQUINA

//MEDIR_RETORNO ***
#define MEDIR_RETORNO_1 14
#define MEDIR_RETORNO_2 15

//SD_LAPIZ ***
#define SD_LAPIZ_COM 9
#define SD_LAPIZ_CORTE 8
#define SD_LAPIZ_COAG 7

//MEDIR_Z ***
#define MEDIR_Z_P1 16
#define MEDIR_Z_P2 17
#define MEDIR_Z_L_COMUN 6

//ACTIVAR_RETORNO
#define ACTIVAR_RETORNO_PIN 2

//ACTIVAR_CORTE
#define ACTIVAR_CORTE_PIN 5

//ACTIVAR_COAG
#define ACTIVAR_COAG_PIN 4

//SONIDO
#define SPEAKER 3

//********************************************************************************************


//DEFINO LA VARIABLE ESTADO PARA CAPTURAR EL ESTADO VIA I2C
int ESTADO = 1;

void setup() {
  
  //CONFIGURACIÓN DE RECEPCIÓN DE DATOS VIA I2C
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  //Serial.begin(9600);           // start serial for output

  //SALIDA DE LA MAQUINA DE ESTADOS
  SET_OUTPUTS_STATES_MACHINE();

}

void loop() {
  
  //Wire.onReceive(receiveEvent); // register event
  TURN_ON_STATES_MACHINE(); //ARRANCA LA MÁQUINA DE ESTADO Y ACTUALIZA LAS SALIDAS

}

void receiveEvent(int howMany) {
  ESTADO = Wire.read();    // receive byte as an integer
  //Serial.println(ESTADO);
}



//DEFINICIÓN DE QUE HACE CADA ESTADO
void ESTADO_INICIO(){

   MEDIR_RETORNO(0);
   SD_LAPIZ(0);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(0);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(0);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(0);
   SONIDO_COAG(0);
}

void ESTADO_MONITOREAR_PLACA(){

   MEDIR_RETORNO(1);
   SD_LAPIZ(1);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(0);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(1);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(0);
   SONIDO_COAG(0);

}

void ESTADO_CORTE_FAIL(){
   MEDIR_RETORNO(1);
   SD_LAPIZ(1);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(0);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(1);
   ALARMA_CORTE_FAIL(1);
   SONIDO_CORTE(0);
   SONIDO_COAG(0);
}

void ESTADO_MONITOREAR_Z(){
   MEDIR_RETORNO(0);
   SD_LAPIZ(0);
   MEDIR_Z(1);
   ACTIVAR_RETORNO(0);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(0);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(0);
   SONIDO_COAG(0);
}

void ESTADO_COAGULAR(){
   MEDIR_RETORNO(0);
   SD_LAPIZ(0);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(1);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(1);
   ALARMA_RETORNO(0);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(0);
   SONIDO_COAG(1);
   tone(SPEAKER,940,10);
}

void ESTADO_CORTAR(){
   MEDIR_RETORNO(0);
   SD_LAPIZ(0);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(1);
   ACTIVAR_CORTE(1);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(0);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(1);
   SONIDO_COAG(0);
   tone(SPEAKER,660,10);
}

void ESTADO_ELECCION_MODO(){
   MEDIR_RETORNO(0);
   SD_LAPIZ(1);
   MEDIR_Z(0);
   ACTIVAR_RETORNO(0);
   ACTIVAR_CORTE(0);
   ACTIVAR_COAG(0);
   ALARMA_RETORNO(0);
   ALARMA_CORTE_FAIL(0);
   SONIDO_CORTE(0);
   SONIDO_COAG(0);
}


//FUNCIONES PARA SETEAR SALIDAS DE LA MAQUINA DE ESTADOS

void SET_OUTPUTS_STATES_MACHINE(){

  pinMode(MEDIR_RETORNO_1, OUTPUT);
  pinMode(MEDIR_RETORNO_2, OUTPUT);
  pinMode(SD_LAPIZ_COM, OUTPUT);
  pinMode(SD_LAPIZ_CORTE, OUTPUT);
  pinMode(SD_LAPIZ_COAG, OUTPUT);
  pinMode(MEDIR_Z_P1, OUTPUT);
  pinMode(MEDIR_Z_P2, OUTPUT);
  pinMode(MEDIR_Z_L_COMUN, OUTPUT);
  pinMode(ACTIVAR_RETORNO_PIN, OUTPUT);
  pinMode(ACTIVAR_CORTE_PIN, OUTPUT);
  pinMode(ACTIVAR_COAG_PIN, OUTPUT);
  
}


void MEDIR_RETORNO(int flag){

  if(flag==0){
    digitalWrite(MEDIR_RETORNO_1,HIGH);
    digitalWrite(MEDIR_RETORNO_2,HIGH);
    }
  else{
    digitalWrite(MEDIR_RETORNO_1,LOW);
    digitalWrite(MEDIR_RETORNO_2,LOW);
    }
}


void SD_LAPIZ(int flag){

  if(flag==0){
    digitalWrite(SD_LAPIZ_COM,HIGH);
    digitalWrite(SD_LAPIZ_CORTE,HIGH);
    digitalWrite(SD_LAPIZ_COAG,HIGH);
    }
  else{
    digitalWrite(SD_LAPIZ_COM,LOW);
    digitalWrite(SD_LAPIZ_CORTE,LOW);
    digitalWrite(SD_LAPIZ_COAG,LOW);
    }
}


void MEDIR_Z(int flag){

  if(flag==0){
    digitalWrite(MEDIR_Z_P1,HIGH);
    digitalWrite(MEDIR_Z_P2,HIGH);
    digitalWrite(MEDIR_Z_L_COMUN,HIGH);
    }
  else{
    digitalWrite(MEDIR_Z_P1,LOW);
    digitalWrite(MEDIR_Z_P2,LOW);
    digitalWrite(MEDIR_Z_L_COMUN,LOW);
    }
}

void ACTIVAR_RETORNO(int flag){

  if(flag==0){
    digitalWrite(ACTIVAR_RETORNO_PIN,HIGH);
    }
  else{
    digitalWrite(ACTIVAR_RETORNO_PIN,LOW);
    }
}

void ACTIVAR_CORTE(int flag){

  if(flag==0){
    digitalWrite(ACTIVAR_CORTE_PIN,HIGH);
    }
  else{
    digitalWrite(ACTIVAR_CORTE_PIN,LOW);
    }
}

void ACTIVAR_COAG(int flag){

  if(flag==0){
    digitalWrite(ACTIVAR_COAG_PIN,HIGH);
    }
  else{
    digitalWrite(ACTIVAR_COAG_PIN,LOW);
    }
}

//DE ACA EN ADELANTE FALTA DEFINIR TANTO ALARMAS COMO SONIDOS DE CORTE =)
void ALARMA_RETORNO(int flag){

  if(flag==0){
    
    }
  else{
    
    }
}

void ALARMA_CORTE_FAIL(int flag){

  if(flag==0){
    
    }
  else{
    
    }
}

void SONIDO_CORTE(int flag){

  if(flag==0){
    
    }
  else{
    
    }
}

void SONIDO_COAG(int flag){

  if(flag==0){
    
    }
  else{
    
    }
}


void TURN_ON_STATES_MACHINE(){

//MAQUINA DE ESTADO
  switch (ESTADO) {
      case 0:
        ESTADO_INICIO();
        //Serial.println("Estado 0"); 
        break;

      case 1:
        ESTADO_MONITOREAR_PLACA();
        //Serial.println("Estado 1");
        break;

      case 2:
        ESTADO_CORTE_FAIL();
        //Serial.println("Estado 2");
        break;

      case 3:
        ESTADO_MONITOREAR_Z();
        //Serial.println("Estado 3");
        break;
      case 4:
        ESTADO_ELECCION_MODO(); // No olvidar agregar un timer en caso de que nunca llegue señal de corte desde el lapiz
      break;

      case 5:
        ESTADO_CORTAR();  //No olvidar agregar un pequeño tiempo para darle tiempo al sensor de corriente
      break;

      case 6:
        ESTADO_COAGULAR();  //No olvidar agregar un pequeño tiempo para darle tiempo al sensor de corriente
      break;
        
      default:
      ESTADO_INICIO();
  }
  
  }


