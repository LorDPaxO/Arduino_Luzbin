
#include <Wire.h> //INCLUYO LIBRERÍA PARA USAR I2C

//DEFINICION DE ESTADOS
#define INICIO 0
#define MONITOREAR_PLACA 1
#define CORTE_FAIL 2
#define MONITOREAR_Z 3
#define ELECCION_MODO 4
#define CORTAR 5
#define COAGULAR 6

//DEFINICIÓN DE SALIDAS DE LA TARJETA QUE GESTIONA LOS PINES DE LA MÁQUINA
#define MEDIR_RETORNO 53
#define SD_LAPIZ 51
#define ACTIVAR_RETORNO 49
#define ACTIVAR_CORTE 47
#define ACTIVAR_COAG 45
#define ALARMA_RETORNO 43 //SOLO SI SE HACE UNA ALARMA VISUAL QUE OCUPE UN PIN FISICO
#define ALARMA_CORTE_FAIL 41
#define SONIDO_CORTE 39
#define SONIDO_COAG 37
#define MEDIR_Z 13


//DEFINO LA VARIABLE ESTADO PARA CAPTURAR EL ESTADO VIA I2C
int ESTADO = 1;

void setup() {

  //CONFIGURACIÓN DE RECEPCIÓN DE DATOS VIA I2C
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  //SALIDA DE LA MAQUINA DE ESTADOS
  SET_OUTPUTS_STATES_MACHINE();

}

void loop() {

  TURN_ON_STATES_MACHINE(); //ARRANCA LA MÁQUINA DE ESTADO Y ACTUALIZA LAS SALIDAS
  delay(500);

}

void receiveEvent(int howMany) {
  ESTADO = Wire.read();    // receive byte as an integer
  //Serial.println(ESTADO);
}



//DEFINICIÓN DE QUE HACE CADA ESTADO
void ESTADO_INICIO(){
   digitalWrite(MEDIR_RETORNO, 0);
   digitalWrite(SD_LAPIZ, 0);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 0);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 0);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 0);

}

void ESTADO_MONITOREAR_PLACA(){
   digitalWrite(MEDIR_RETORNO, 1);
   digitalWrite(SD_LAPIZ, 1);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 0);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 1);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 0);
}

void ESTADO_CORTE_FAIL(){
   digitalWrite(MEDIR_RETORNO, 1);
   digitalWrite(SD_LAPIZ, 1);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 0);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 1);
   digitalWrite(ALARMA_CORTE_FAIL, 1);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 0);
}

void ESTADO_MONITOREAR_Z(){
   digitalWrite(MEDIR_RETORNO, 0);
   digitalWrite(SD_LAPIZ, 0);
   digitalWrite(MEDIR_Z, 1);
   digitalWrite(ACTIVAR_RETORNO, 0);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 0);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 0);
}

void ESTADO_COAGULAR(){
   digitalWrite(MEDIR_RETORNO, 0);
   digitalWrite(SD_LAPIZ, 0);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 1);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 1);
   digitalWrite(ALARMA_RETORNO, 0);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 1);
}

void ESTADO_CORTAR(){
   digitalWrite(MEDIR_RETORNO, 0);
   digitalWrite(SD_LAPIZ, 0);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 1);
   digitalWrite(ACTIVAR_CORTE, 1);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 0);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 1);
   digitalWrite(SONIDO_COAG, 0);
}

void ESTADO_ELECCION_MODO(){
   digitalWrite(MEDIR_RETORNO, 0);
   digitalWrite(SD_LAPIZ, 1);
   digitalWrite(MEDIR_Z, 0);
   digitalWrite(ACTIVAR_RETORNO, 0);
   digitalWrite(ACTIVAR_CORTE, 0);
   digitalWrite(ACTIVAR_COAG, 0);
   digitalWrite(ALARMA_RETORNO, 0);
   digitalWrite(ALARMA_CORTE_FAIL, 0);
   digitalWrite(SONIDO_CORTE, 0);
   digitalWrite(SONIDO_COAG, 0);
}



//FUNCIONES PARA SETEAR SALIDAS DE LA MAQUINA DE ESTADOS

void SET_OUTPUTS_STATES_MACHINE(){

  pinMode(MEDIR_RETORNO, OUTPUT);
  pinMode(SD_LAPIZ, OUTPUT);
  pinMode(ACTIVAR_RETORNO, OUTPUT);
  pinMode(ACTIVAR_CORTE, OUTPUT);
  pinMode(ACTIVAR_COAG, OUTPUT);
  pinMode(ALARMA_RETORNO, OUTPUT);
  pinMode(ALARMA_CORTE_FAIL, OUTPUT);
  pinMode(SONIDO_CORTE, OUTPUT);
  pinMode(SONIDO_COAG, OUTPUT);
  pinMode(MEDIR_Z, OUTPUT);

}

void TURN_ON_STATES_MACHINE(){

//MAQUINA DE ESTADO
  switch (ESTADO) {
      case 0:
        ESTADO_INICIO();
        Serial.println("Estado 0"); 
        break;

      case 1:
        ESTADO_MONITOREAR_PLACA();
        Serial.println("Estado 1");
        break;

      case 2:
        ESTADO_CORTE_FAIL();
        Serial.println("Estado 2");
        break;

      case 3:
        ESTADO_MONITOREAR_Z();
        Serial.println("Estado 3");
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
      ESTADO=0;
  }
}

