
#include <Nextion.h>

#define RxD A1
#define TxD A0
String Modo_Corte = "";
String Modo_Coag = "";

SoftwareSerial nextion(RxD,TxD); //Recordar que puedo usar el virtual o puertos en hardware
int Potencia_Corte=0;
int Potencia_Coag=0;
int Pot=0;
boolean bt_puro=0;
boolean bt_mixto=0;
boolean bt_sangrado=0;

boolean bt_alto=0;
boolean bt_medio=0;
boolean bt_bajo=0;



Nextion myNextion(nextion,9600); //Se crea un objeto tipo Nextion que se va a comunicar a 9600 bauds

//Inicializar todo lo necesario
void setup() {
  
  Serial.begin(9600);
  myNextion.init();
  //nextion.begin(9600);
}


void loop() {


  
}


void CAPTURA_POTENCIA_LCD(){
  
  Pot = myNextion.getComponentValue("Home.va0");
  if(Pot>0 && Pot<=100){
      Potencia_Corte=Pot;
    }
    
  Pot = myNextion.getComponentValue("Home.va1");
  if(Pot>0 && Pot<=100){
      Potencia_Coag=Pot;
    }
  }

void CAPTURA_MODO_CORTE(){
  
  bt_puro = myNextion.getComponentValue("Home.bt0");
  bt_mixto = myNextion.getComponentValue("Home.bt1");
  bt_sangrado = myNextion.getComponentValue("Home.bt2");

  if(bt_puro){
      Modo_Corte = "Puro";
    }else if(bt_mixto){
      Modo_Corte = "Mixto";
      } else if(bt_sangrado){
          Modo_Corte = "Sangrado";
        } else{
          Modo_Corte = "No_Corte";
          }
  }

void CAPTURA_MODO_COAG(){
  
  bt_alto = myNextion.getComponentValue("Home.bt3");
  bt_medio = myNextion.getComponentValue("Home.bt4");
  bt_bajo = myNextion.getComponentValue("Home.bt5");

  if(bt_alto){
      Modo_Coag = "Alto";
    }else if(bt_medio){
      Modo_Coag = "Medio";
      } else if(bt_bajo){
          Modo_Coag = "Bajo";
        } else{
          Modo_Coag = "No_Coag";
          }
  }
void ALARMA_PLACA(){
  //myNextion.sendCommand("page Alerta_Placa");
  myNextion.sendCommand("vis p0,1");
  myNextion.sendCommand("p0.pic=29");
  }


void CORTANDO(){
  myNextion.sendCommand("Home.n0.pco=63488");    
  }

void COAGULANDO(){
  myNextion.sendCommand("Home.n1.pco=63488");    
  }

void STANDBY(){
  myNextion.sendCommand("Home.n0.pco=65535");    
  }





  
