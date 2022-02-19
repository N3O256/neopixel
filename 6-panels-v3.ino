#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN 2
#define NUMPIXELS 48

RF24 radio(4, 5); // CE (4), CSN (5)
const byte address[6] = "00001";

int transmit = 3;
int lastState = transmit;

int brightness = 100;
int changingSpeed = 200;


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//for loading light
int colors2[10][3] = {{255, 0, 0}, {255, 66, 0}, {255, 255, 0}, 
                    {0, 255, 0},
                    {0, 255, 255},
                    {0, 100, 255}, {0, 0, 255},
                    {255, 0, 255},
                    {255, 0, 129}, {255, 0, 66}};

int j = 0;

void setup() {
  pixels.begin();

  Serial.begin(9600);

  radio.begin();                      //Starting the Wireless communication
  radio.openReadingPipe(0, address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);      //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setChannel(115);
  radio.startListening();
}

void loop() {
  remote();
}

void remote(){
  receive1();
  lastState = transmit;

  if(lastState == 1){
    loadingLight();
  }else if(lastState == 2){
    turningLight();
  }else if(lastState == 3){
    whiteLight();
  }else if(lastState > 3 && lastState < 17){
    customColor();
  }
  
}

void turningLight(){
  for(int i = 0; i < NUMPIXELS; i+=3){
    if(j > 9){
      j = 0;
    }
    pixels.setPixelColor(i, pixels.Color(colors2[j][0], colors2[j][1], colors2[j][2]));
    pixels.setPixelColor(i+1, pixels.Color(colors2[j][0], colors2[j][1], colors2[j][2]));
    pixels.setPixelColor(i+2, pixels.Color(colors2[j][0], colors2[j][1], colors2[j][2]));
    pixels.setBrightness(brightness);
    pixels.show();
    j++;
  }
  delay(changingSpeed);
  j--;
}

void customColor(){
  int r = 0;
  int g = 0;
  int b = 0;
  if(lastState = 4){
    r = 255;
    g = 255;
    b = 255;
  }else if(lastState = 5){
    r = 0;
    g = 255;
    b = 150;
  }else if(lastState = 6){
    r = 0;
    g = 255;
    b = 0;
  }else if(lastState = 7){
    r = 255;
    g = 255;
    b = 0;
  }else if(lastState = 8){
    r = 255;
    g = 170;
    b = 0;
  }else if(lastState = 9){
    r = 255;
    g = 120;
    b = 0;
  }else if(lastState = 10){
    r = 255;
    g = 0;
    b = 0;
  }

  else if(lastState = 11){
    r = 255;
    g = 0;
    b = 255;
  }else if(lastState = 12){
    r = 160;
    g = 0;
    b = 255;
  }else if(lastState = 13){
    r = 0;
    g = 0;
    b = 255;
  }else if(lastState = 14){
    r = 0;
    g = 130;
    b = 255;
  }else if(lastState = 15){
    r = 0;
    g = 255;
    b = 255;
  }else if(lastState = 16){
    r = 0;
    g = 255;
    b = 210;
  }
  
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, r, b, g);
  }
  
  pixels.setBrightness(brightness);
  pixels.show();
}

void loadingLight(){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < NUMPIXELS; j++){
      pixels.setPixelColor(j, pixels.Color(colors2[i][0], colors2[i][1], colors2[i][2]));
      pixels.setBrightness(brightness);
      pixels.show();
      delay(changingSpeed);
      //updateValues();
    }
  }
}

void whiteLight(){
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, 255, 255, 255);
  }
  pixels.setBrightness(brightness);
  pixels.show();
}

void receive1(){
  if(radio.available()){
    radio.read(&transmit, sizeof(transmit));
    Serial.println(transmit);
  }else{
    Serial.println("not available");
  }
  delay(500);
}