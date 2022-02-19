#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN (9, 10)
const byte address[6] = "00001";

int xAxis1 = 0;
int yAxis1 = 0;
boolean buttonAxis = false;
boolean buttonAxisLast = false;

boolean button1 = false;
boolean button1Last = false;
boolean button2 = false;
boolean button2Last = false;
boolean button3 = false;
boolean button3Last = false;

int receive = 0;
int transmit = 0;
int number = 0;

void setup() {
  Serial.begin(9600);
  
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setChannel(115);
  radio.stopListening();
}

void loop() {
  readValues();
  transmit = getChanges();
  if(!radio.write(&transmit, sizeof(transmit))){
    Serial.println("It didn't work");
  }else{
    Serial.println(transmit);
  }
}

void readValues(){
  button1 = digitalRead(2);
  button2 = digitalRead(3);
  button3 = digitalRead(4);
  buttonAxis = digitalRead(7);
}

int getChanges(){
  if(button1 != button1Last){
    receive = 1;
    button1Last = button1;
  }

  if(button2 != button2Last){
    receive = 2;
    button2Last = button2;
  }

  if(button3 != button3Last){
    receive = 3;
    button3Last = button3;
  }

  if(buttonAxis != buttonAxisLast){
    getIntValueOfCustom();
    receive = number;
    buttonAxisLast = buttonAxis;
  }

  return receive;
}

void getIntValueOfCustom(){  
  xAxis1 = analogRead(A2);
  map(xAxis1, 0, 1023, -18, 18);
  
  yAxis1 = analogRead(A3);
  map(yAxis1, 0, 1023, -18, 18);
  
  if(yAxis1 == 0 && xAxis1 == 0){
    number = 4;
  }else if(yAxis1 < 6 && xAxis1 > 0){
    number = 5;
  }else if(yAxis1 > 6 && yAxis1 < 12 && xAxis1 > 0){
    number = 6;
  }else if(yAxis1 >= 12 && xAxis1 > 0){
    number = 7;
  }else if(yAxis1 >= 12 && xAxis1 < 0){
    number = 8;
  }else if(yAxis1 > 6 && yAxis1 < 12 && xAxis1 < 0){
    number = 9;
  }else if(yAxis1 < 6 && xAxis1 > 0){
    number = 10;
  }

  else if(yAxis1 < 6 && xAxis1 > 0){
    number = 11;
  }else if(yAxis1 > 6 && yAxis1 < 12 && xAxis1 > 0){
    number = 12;
  }else if(yAxis1 >= 12 && xAxis1 > 0){
    number = 13;
  }else if(yAxis1 >= 12 && xAxis1 < 0){
    number = 14;
  }else if(yAxis1 > 6 && yAxis1 < 12 && xAxis1 < 0){
    number = 15;
  }else if(yAxis1 < 6 && xAxis1 > 0){
    number = 16;
  }
}
