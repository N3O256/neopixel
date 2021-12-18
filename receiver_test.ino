#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN (5, 6)
const byte address[6] = "00001";

String s;

void setup() {
  Serial.begin(9600);
    
  radio.begin();                      //Starting the Wireless communication
  radio.openReadingPipe(0, address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);      //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();
}

void loop() {
  if(radio.available()){
    radio.read(&s, sizeof(s));
    Serial.println(s);
  }else{
    Serial.println("not available");
  }
}