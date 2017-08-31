

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}



  Wire.beginTransmission(Slave_Add);  // Envia los 7 bits de direccion del AD5933 + el bit de escritura (0), para comenzar
  Wire.write(PCB_RELES_1);
  Wire.write(PCB_RELES_2);
  Wire.endTransmission();

//rEVISAR oNrQUEST

/*
  Wire.beginTransmission(Slave_Add);  // Envia los 7 bits de direccion del AD5933 + el bit de escritura (0), para comenzar
  Wire.write(Data_1);
  Wire.write(Data_2);
  Wire.endTransmission();
*/
