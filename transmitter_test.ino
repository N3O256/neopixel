#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5); // CE, CSN (9, 10)
const byte address[6] = "00001";

int s = 12;

void setup() {
  Serial.begin(9600);
  
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setChannel(115);
  radio.stopListening();
}

void loop() {
  if(!radio.write(&s, sizeof(s))){
    Serial.println("It didn't work");
  }else{
    Serial.println("IT DID WORK");
  }
}