/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. this_pin is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
  
  modified 8 Sep 2016
  by Colby Newman
*/
#define this_pin 2
int count=2;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin this_pin as an output.
  //pinMode(this_pin, OUTPUT);
  configurar_salidas();
  salidas_en_ceros();
  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {

  //digitalWrite(this_pin,HIGH);
  count=2;
  while(count<10){
    digitalWrite(count, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    count = count+1;
    //Serial.print(count);
    //digitalWrite(count, LOW);    // turn the LED off by making the voltage LOW
    //delay(10000);                       // wait for a second
  }

   count=2;
  while(count<10){
    digitalWrite(count, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    count = count+1;
    //Serial.print(count);
    //digitalWrite(count, LOW);    // turn the LED off by making the voltage LOW
    //delay(10000);                       // wait for a second
  }
  
}
void configurar_salidas(){
   count=2;
   while(count<10){
      pinMode(count,OUTPUT);
      count = count+1;
    }
}

void salidas_en_ceros(){
   count=2;
   while(count<10){
      digitalWrite(count,HIGH);
      count = count+1;
    }
}
