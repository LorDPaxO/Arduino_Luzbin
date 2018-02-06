

/////////////////////////////////////////////////////////////////////
/////////////*******************************************/////////////
/////////////***********#1 BIOIMPEDENCEMETER************/////////////
//ACÁ SE LEEN LAS ENTRADAS DE LA MÁQUINA DE ESTADOS, SE EJECUTA LA LÓGICA Y SE ENVIAN LAS ACCIONES
//AL RESTO DE PLACA, ADICIONAL CAPTURA Y ACTUALIZA LOS DATOS DE LA PANTALLA NEXTION
/////////////*******************************************/////////////
/////////////////////////////////////////////////////////////////////


#include <AD5933.h>
#include <Wire.h>
#include <Nextion.h>
byte estado_I2C=0;
AD5933 Bio(19200);

#define RxD 7
#define TxD 6
String Modo_Corte = "";
String Modo_Coag = "";

SoftwareSerial nextion(RxD,TxD); //Recordar que puedo usar el virtual o puertos en hardware
int Potencia_Corte=0;
int Potencia_Coag=0;
int Pot=0;
int t;
boolean bt_puro=0;
boolean bt_mixto=0;
boolean bt_sangrado=0;

boolean bt_alto=0;
boolean bt_medio=0;
boolean bt_bajo=0;

Nextion myNextion(nextion,9600);

//DEFINICION DE ESTADOS
#define INICIO 0
#define MONITOREAR_PLACA 1
#define CORTE_FAIL 2
#define MONITOREAR_Z 3
#define ELECCION_MODO 4
#define CORTAR 5
#define COAGULAR 6


//DEFINICIÓN DE ENTRADAS
#define SD_LAPIZ_HIGH 5
#define COR_ON 3
#define COAG_ON 4
//#define CORTE_C 16   //PROBAR SI SIRVE EL SENSOR DE CORRIENTE, SI NO, NO VAN LAS LINEAS 31 Y 32
//#define COAG_C 17   //PROBAR SI SIRVE EL SENSOR DE CORRIENTE, SI NO, NO VAN LAS LINEAS 31 Y 32

//DEFINICION DE SALIDAS DEL SWITCH FUENTE CONMUTADA
#define ACT_SW 17


//Creo los buffer de las entradas para almacenar el estado de todas las e8ntradas y trabajar de la misma forma que un plc
int ESTADO = 0;
boolean PLACA_RETORNO_S = 0;
boolean COR_ON_S = 0;
boolean COAG_ON_S = 0;

boolean CORTE_C_S = 0;
boolean COAG_C_S = 0;

boolean Z_ON_S = 0;


//Variables para el control DC
boolean State_DC = false;
int Bio_Val=0;
int Pot_Val=0;
int Modo_Corte_Val=1;
float Val;
float Vrms;
float Vamp;
int Volt_Value;

byte Bio_ValF;
byte Bio_ValS;


void setup() {

  Wire.begin(); // join i2c bus
  Serial.begin(9600);
  myNextion.init();
  pinMode(SD_LAPIZ_HIGH,OUTPUT);
  pinMode(ACT_SW, OUTPUT);
  digitalWrite(SD_LAPIZ_HIGH,HIGH);
  digitalWrite(ACT_SW,HIGH);
  
  //ENTRADAS DE LA MAQUINA DE ESTADOS
  DEFINE_INPUTS_STATES_MACHINE();

}

void loop() {

  READ_INPUTS_STATES_MACHINE(); //LEE Y ALMACENA EL ESTADO DE LAS ENTRADAS DE LA MAQUINA DE ESTADO
  TURN_ON_STATES_MACHINE(); //ARRANCA LA MÁQUINA DE ESTADO
  SEND_DATA_I2C(); //ENVIA LOS DATOS POR MEDIO DE I2C

}


//DEFINICIÓN DE QUE HACE CADA ESTADO
//NO LO DEFINO ACÁ SINO EN EL MICRO QUE GESTIONA LAS SALIDAS

//FUNCIÓN PARA LEER Y ALMACENAR ENTRADAS
void READ_INPUTS_STATES_MACHINE(){

  PLACA_RETORNO_REQUEST(); // CAPTURO Y ALMACENO EN EL BUFER
  Z_ON_REQUEST();
  COR_ON_S = digitalRead(COR_ON);
  COAG_ON_S = digitalRead(COAG_ON);
//  CORTE_C_S = digitalRead(CORTE_C);
//  COAG_C_S = digitalRead(COAG_C);
}


//FUNCIONES PARA SETEAR ENTRADAS Y SALIDAS DE LA MAQUINA DE ESTADOS
void DEFINE_INPUTS_STATES_MACHINE(){

  pinMode(COR_ON, INPUT);
  pinMode(COAG_ON, INPUT);
//  pinMode(CORTE_C, INPUT_PULLUP);
//  pinMode(COAG_C, INPUT_PULLUP);
}

void SEND_DATA_I2C() {

    //ENVIO DATO DE ESTADO A LA PLACA GESTORA DE SALIDAS
    estado_I2C = ESTADO;
    Serial.println(estado_I2C);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(estado_I2C);    // sends one byte
    Wire.endTransmission();    // stop transmitting
    delay(10);
}


void PLACA_RETORNO_REQUEST(){

    int Valor_Impedancia = Bio.impedance();
    if(Valor_Impedancia<300){
        PLACA_RETORNO_S = true;
      }else{
        PLACA_RETORNO_S = false;  
      }
  }

void Z_ON_REQUEST(){

    int Valor_Z = Bio.impedance();
    if(ESTADO==3){
        Bio_Val=Valor_Z; //Creo un buffer para el valor de bioimpedancia
      }
    Serial.println(Valor_Z);
    if(Valor_Z<1000){
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
        STANDBY();
        ESTADO = MONITOREAR_PLACA;

        break;

      case 1:
        //Serial.println("Estado 1");
        ALARMA_PLACA();
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
        ALARMA_PLACA();
        if(!COR_ON_S & !COAG_ON_S==1){
            ESTADO = MONITOREAR_PLACA;
        }
        break;

      case 3:
          //Serial.println("Estado 3");
          PLACA_OK();
          if(Z_ON_S==1){
              ESTADO = ELECCION_MODO;
              I2C_CONTROL_DC();
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
        CORTANDO();
        delay(5000); //Borrar por favor, son solo para pruebas
        if(1){
            ESTADO = INICIO;
        } else {
            // ME QUEDO EN EL MISMO ESTADO
        }
      break;

      case 6:
        //Serial.println("Estado 6");
        COAGULANDO();
        delay(30000); //Borrar por favor, son solo para pruebas
        if(1){
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


void I2C_CONTROL_DC(){

  CAPTURA_POTENCIA_LCD(1);
  Bio_Val = 800;
  //Pot_Val = 517;
  Calc_Power(Pot_Val, Bio_Val, Modo_Corte_Val); //Valor de bioimpedancia
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(Pot_Val);               // Tension de Salida
  Wire.endTransmission();    // stop transmitting
  Serial.println("DATO DE VOLTAJE A LA SALIDA ES:");
  Serial.println(Pot_Val);
  }

//conversor para hacer comunicación I2C 

void Calc_Power (long P_Value, long B_Value, float Cycle_Value)
{  

  Val = B_Value * P_Value; 
  Vrms = sqrt(Val);
  Vamp = Vrms/(sqrt(2*Cycle_Value));                         // Los valores de Factor de uso Fac_Use se calcularon al obtener la formula Vrms = Vamp/(sqrt(2*Tciclo util))   
  Volt_Value = Vamp/13;
  Serial.println("Volt_Value");
  Serial.println(Volt_Value);
}


void CAPTURA_POTENCIA_LCD(int sel){
  
  Pot = myNextion.getComponentValue("Home.va0");
  if(sel==1 && Pot>0 && Pot<=100){
      Potencia_Corte=Pot;
      Pot_Val=Potencia_Corte;
    }
    
  Pot = myNextion.getComponentValue("Home.va1");
  if(sel==2 && Pot>0 && Pot<=100){
      Potencia_Coag=Pot;
      Pot_Val=Potencia_Coag;
    }
  }

void CAPTURA_MODO_CORTE(){
  
  bt_puro = myNextion.getComponentValue("Home.bt0");
  bt_mixto = myNextion.getComponentValue("Home.bt1");
  bt_sangrado = myNextion.getComponentValue("Home.bt2");

  if(bt_puro){
      Modo_Corte = "Puro";
      Modo_Corte_Val=1;
    }else if(bt_mixto){
      Modo_Corte = "Mixto";
      Modo_Corte_Val=2;
      } else if(bt_sangrado){
          Modo_Corte = "Sangrado";
          Modo_Corte_Val=3;
        } else{
          Modo_Corte = "No_Corte";
          Modo_Corte_Val=0;
          }
  }

void CAPTURA_MODO_COAG(){
  
  bt_alto = myNextion.getComponentValue("Home.bt3");
  bt_medio = myNextion.getComponentValue("Home.bt4");
  bt_bajo = myNextion.getComponentValue("Home.bt5");

  if(bt_alto){
      Modo_Coag = "Alto";
      Modo_Corte_Val=4;
    }else if(bt_medio){
      Modo_Coag = "Medio";
      Modo_Corte_Val=5;
      } else if(bt_bajo){
          Modo_Coag = "Bajo";
          Modo_Corte_Val=6;
        } else{
          Modo_Coag = "No_Coag";
          Modo_Corte_Val=0;
          }
  }
void ALARMA_PLACA(){
  //myNextion.sendCommand("page Alerta_Placa");
  myNextion.sendCommand("vis Home.p0,1");
  myNextion.sendCommand("Home.p0.pic=14");
  }

void PLACA_OK(){
  //myNextion.sendCommand("page Alerta_Placa");
  myNextion.sendCommand("vis Home.p0,1");
  myNextion.sendCommand("Home.p0.pic=10");
  }


void CORTANDO(){
  //myNextion.sendCommand("page Cortando");
  myNextion.sendCommand("click b4,1");
  
  CAPTURA_POTENCIA_LCD(1);
  CAPTURA_MODO_CORTE();
  delay(50);
  digitalWrite(ACT_SW, LOW);
  
  //**Actualizar por cambio de pantalla a Cortando
  }

void COAGULANDO(){
  //myNextion.sendCommand("page Coagulando");
  myNextion.sendCommand("click b5,1");
  CAPTURA_POTENCIA_LCD(2);
  CAPTURA_MODO_COAG();
  delay(50);
  digitalWrite(ACT_SW, LOW);  
  //**Actualizar por cambio de pantalla a Coagulando
  }

void STANDBY(){
  myNextion.sendCommand("page Home");
  delay(50);
  digitalWrite(ACT_SW, HIGH);
  //**Actualizar por cambio de pantalla a Home
  }



