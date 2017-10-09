/////////////////////////////////////////////////////////////////////
/////////////*******************************************/////////////
/////////////***********#1 BIOIMPEDENCEMETER************/////////////
//ACÁ SE LEEN LAS ENTRADAS DE LA MÁQUINA DE ESTADOS, SE EJECUA LA LÓGICA Y SE ENVIAN LAS ACCIONES
//AL RESTO DE PLACA, ADICIONAL CAPTURA Y ACTUALIZA LOS DATOS DE LA PANTALLA NEXTION
/////////////*******************************************/////////////
/////////////////////////////////////////////////////////////////////




#include <AD5933.h>
#include <Wire.h>
byte estado_I2C=0;
AD5933 Bio(9600);

//DEFINICION DE ESTADOS
#define INICIO 0
#define MONITOREAR_PLACA 1
#define CORTE_FAIL 2
#define MONITOREAR_Z 3
#define ELECCION_MODO 4
#define CORTAR 5
#define COAGULAR 6


//DEFINICIÓN DE ENTRADAS

#define COR_ON 8
#define COAG_ON 9
#define CORTE_C 4   //PROBAR SI SIRVE EL SENSOR DE CORRIENTE, SI NO, NO VAN LAS LINEAS 31 Y 32
#define COAG_C 3    //PROBAR SI SIRVE EL SENSOR DE CORRIENTE, SI NO, NO VAN LAS LINEAS 31 Y 32


//Creo los buffer de las entradas para almacenar el estado de todas las entradas y trabajar de la misma forma que un plc
int ESTADO = 0;
boolean PLACA_RETORNO_S = 0;
boolean COR_ON_S = 0;
boolean COAG_ON_S = 0;
boolean CORTE_C_S = 0;
boolean COAG_C_S = 0;
boolean Z_ON_S = 0;


void setup() {

  Wire.begin(); // join i2c bus
  Serial.begin(9600);
  //ENTRADAS DE LA MAQUINA DE ESTADOS
  DEFINE_INPUTS_STATES_MACHINE();

}

void loop() {

  READ_INPUTS_STATES_MACHINE(); //LEE Y ALMACENA EL ESTADO DE LAS ENTRADAS DE LA MAQUINA DE ESTADO
  TURN_ON_STATES_MACHINE(); //ARRANCA LA MÁQUINA DE ESTADO
  SEND_STATE_I2C(); //ENVIA EL DATO DEL ESTADO AL MICROCONTROLADOR QUE GESTIONA LAS SALIDAS

}


//DEFINICIÓN DE QUE HACE CADA ESTADO
//NO LO DEFINO ACÁ SINO EN EL MICRO QUE GESTIONA LAS SALIDAS

//FUNCIÓN PARA LEER Y ALMACENAR ENTRADAS
void READ_INPUTS_STATES_MACHINE(){

  PLACA_RETORNO_REQUEST(); // CAPTURO Y ALMACENO EN EL BUFER
  Z_ON_REQUEST();
  COR_ON_S = digitalRead(COR_ON);
  COAG_ON_S = digitalRead(COAG_ON);
  CORTE_C_S = digitalRead(CORTE_C);
  COAG_C_S = digitalRead(COAG_C);
}


//FUNCIONES PARA SETEAR ENTRADAS Y SALIDAS DE LA MAQUINA DE ESTADOS
void DEFINE_INPUTS_STATES_MACHINE(){

  pinMode(COR_ON, INPUT);
  pinMode(COAG_ON, INPUT);
  pinMode(CORTE_C, INPUT);
  pinMode(COAG_C, INPUT);
}

void SEND_STATE_I2C() {

  estado_I2C = ESTADO;
  Serial.println(estado_I2C);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(estado_I2C);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(10);
}


void PLACA_RETORNO_REQUEST(){

    int Valor_Impedancia = Bio.impedance();
    Serial.println(Valor_Impedancia);
    if(Valor_Impedancia<480){
        PLACA_RETORNO_S = true;
      }else{
        PLACA_RETORNO_S = false;  
      }
      Serial.println("Placa de Retorno");
      Serial.println(PLACA_RETORNO_S);
  }

void Z_ON_REQUEST(){

    int Valor_Z = Bio.impedance();
    if(Valor_Z<2500){
        Z_ON_S = true;
      }else{
        Z_ON_S = false;  
      }
  }


void TURN_ON_STATES_MACHINE(){

//MAQUINA DE ESTADO
  switch (ESTADO) {
      case 0:
        //Serial.println("Estado 0");
        ESTADO = MONITOREAR_PLACA;
        break;

      case 1:
        //Serial.println("Estado 1");
        if(PLACA_RETORNO_S==1){
            ESTADO = MONITOREAR_Z;
        } else if((COR_ON_S || COAG_ON_S) & !PLACA_RETORNO_S){
            ESTADO = CORTE_FAIL;
        } else {
            //SIGO EN EL MISMO ESTADO;
        }
        break;

      case 2:
        //Serial.println("Estado 2");
        if(!COR_ON_S & !COAG_ON_S==1){
            ESTADO = MONITOREAR_PLACA;
        }
        break;

      case 3:
          //Serial.println("Estado 3");
          if(Z_ON_S==1){
              ESTADO = ELECCION_MODO;
          } else {
              //ESTADO = MONITOREAR_PLACA;
          }
        break;
        
      case 4:
        //Serial.println("Estado 4");
        if(COR_ON_S==1){
            ESTADO = CORTAR;
        } else if(COAG_ON_S){
            ESTADO = COAGULAR;
        } else {
            //sigue en el mismo estado
        } 
      break;

      case 5:
        //Serial.println("Estado 5");
        if(CORTE_C_S==1){
            ESTADO = INICIO;
        } else {
            // ME QUEDO EN EL MISMO ESTADO
        }
      break;

      case 6:
        //Serial.println("Estado 6");
        if(COAG_C_S==1){
            ESTADO = INICIO;
        } else {
            // ME QUEDO EN EL MISMO ESTADO
        }
      break;
        
      default:
      //Serial.println("Estado por default");
      ESTADO=0;
  }
}

