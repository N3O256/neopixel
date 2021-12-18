#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(5, 6); // CE, CSN (9, 10)
const byte address[6] = "00001";

int xAxis = 0;
int yAxis = 0;
boolean buttonAxis;

boolean button1;
boolean button2;
boolean button3;

int brightness = 100;
int changingSpeed = 200;

void setup() {
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();
}

void loop() {
  xAxis = analogRead(A3);
  map(xAxis, 0, 1023, -18, 18);
  radio.write(&xAxis, sizeof(xAxis));
  yAxis = analogRead(A2);
  map(yAxis, 0, 1023, -18, 18);
  radio.write(&yAxis, sizeof(yAxis));
  buttonAxis = digitalRead(2);
  radio.write(&buttonAxis, sizeof(buttonAxis));

  button1 = digitalRead(3);
  radio.write(&button1, sizeof(button1));
  button2 = digitalRead(4);
  radio.write(&button2, sizeof(button2));
  button3 = digitalRead(8);
  radio.write(&button3, sizeof(button3));

  brightness = analogRead(A0);
  map(brightness, 0, 1023, 0, 100);
  radio.write(&brightness, sizeof(brightness));
  changingSpeed = analogRead(A1);
  radio.write(&changingSpeed, sizeof(changingSpeed));
}