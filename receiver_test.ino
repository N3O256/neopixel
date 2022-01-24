#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN (4, 5)
const byte address[6] = "00001";

int s = 0;

void setup() {
  Serial.begin(9600);
    
  radio.begin();                      //Starting the Wireless communication
  radio.openReadingPipe(0, address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);      //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setChannel(115);
  radio.startListening();
}

void loop() {
  if(radio.available()){
    radio.read(&s, sizeof(s));
    Serial.println(s);
  }else{
    Serial.println("not available");
  }
  delay(500);
}