#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN (9, 10)
const byte address[6] = "00001";

String s = "This is working";

void setup() {
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();
}

void loop() {
  radio.write(&s, sizeof(s));
  delay(200);
}