
//DEFINICION DE ESTADOS
#define INICIO 0
#define MONITOREAR_PLACA 1
#define CORTE_FAIL 2
#define MONITOREAR_Z 3
#define ELECCION_MODO 4
#define CORTAR 5
#define COAGULAR 6


//DEFINICIÓN DE ENTRADAS
//Recordar que las entradas están asociadas a pines físicos
//Poneras como INPUTS en el void Setup 

//FALTA ASOCIAR LAS ENTRADAS A PINES DIGITALES DISPONIBLES
#define PLACA_RETORNO 7
#define COR_ON 6
#define COAG_ON 5
#define CORTE_C 4
#define COAG_C 3
#define Z_ON 2


//DEFINICIÓN DE SALIDAS
//Recordar que las entradas están asociadas a pines físicos
//Poneras como OUTPUTS en el void Setup y hacer señales internas donde haga falta

//FALTA ASOCIAR LAS ENTRADAS A PINES DIGITALES DISPONIBLES
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

int ESTADO = 0;
boolean PLACA_RETORNO_S = 0;
boolean COR_ON_S = 0;
boolean COAG_ON_S = 0;
boolean CORTE_C_S = 0;
boolean COAG_C_S = 0;
boolean Z_ON_S = 0;


void setup() {

  //ENTRADAS DE LA MAQUINA DE ESTADOS
  SET_INPUTS_STATES_MACHINE();

  //SALIDA DE LA MAQUINA DE ESTADOS
  SET_OUTPUTS_STATES_MACHINE();

}

void loop() {

  //Hacer case para máquina de estados
  //Creo que se puede incluir esto en el uC principal para no hacer mas conexiones fisicas
  READ_INPUTS_STATES_MACHINE(); //LEE Y ALMACENA EL ESTADO DE LAS ENTRADAS DE LA MAQUINA DE ESTADOS
  TURN_ON_STATES_MACHINE(); //ARRANCA LA MÁQUINA DE ESTADO Y ACTUALIZA LAS SALIDAS
  //Dependiendo de la señal puedo o no agregar delays para darle tiempo de respuesta a los reles.

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

//FUNCIÓN PARA LEER Y ALMACENAR ENTRADAS
void READ_INPUTS_STATES_MACHINE(){
  PLACA_RETORNO_S = digitalRead(PLACA_RETORNO);
  COR_ON_S = digitalRead(COR_ON);
  COAG_ON_S = digitalRead(COAG_ON);
  CORTE_C_S = digitalRead(CORTE_C);
  COAG_C_S = digitalRead(COAG_C);
  Z_ON_S = digitalRead(Z_ON);
}


//FUNCIONES PARA SETEAR ENTRADAS Y SALIDAS DE LA MAQUINA DE ESTADOS
void SET_INPUTS_STATES_MACHINE(){

  pinMode(PLACA_RETORNO, INPUT);
  pinMode(COR_ON, INPUT);
  pinMode(COAG_ON, INPUT);
  pinMode(CORTE_C, INPUT);
  pinMode(COAG_C, INPUT);
  pinMode(Z_ON, INPUT);

}

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
        ESTADO = MONITOREAR_PLACA;
        break;

      case 1:
        ESTADO_MONITOREAR_PLACA();
        if(PLACA_RETORNO_S==1){
            ESTADO = MONITOREAR_Z;
        } else if((COR_ON_S || COAG_ON_S) & !PLACA_RETORNO_S){
            ESTADO = CORTE_FAIL;
        } else {
            //SIGO EN EL MISMO ESTADO;
        }
        break;

      case 2:
        ESTADO_CORTE_FAIL();
        if(!COR_ON_S & !COAG_ON_S==1){
            ESTADO = MONITOREAR_PLACA;
        }
        break;

      case 3:
        ESTADO_MONITOREAR_Z();
          if(Z_ON_S==1){
              ESTADO = ELECCION_MODO;
          } else {
              ESTADO = MONITOREAR_PLACA;
          }
        break;
      case 4:
        ESTADO_ELECCION_MODO(); // No olvidar agregar un timer en caso de que nunca llegue señal de corte desde el lapiz
        if(COR_ON_S==1){
            ESTADO = CORTAR;
        } else if(COAG_ON_S){
            ESTADO = COAGULAR;
        } else {
            //sigue en el mismo estado
        } 
      break;

      case 5:
        ESTADO_CORTAR();  //No olvidar agregar un pequeño tiempo para darle tiempo al sensor de corriente
        if(CORTE_C_S==1){
            ESTADO = ESTADO_INICIO;
        } else {
            // ME QUEDO EN EL MISMO ESTADO
        }
      break;

      case 6:
        ESTADO_COAGULAR();  //No olvidar agregar un pequeño tiempo para darle tiempo al sensor de corriente
        if(COAG_C_S==1){
            ESTADO = ESTADO_INICIO;
        } else {
            // ME QUEDO EN EL MISMO ESTADO
        }
      break;
        
      default:
      ESTADO=0;
  }
}

