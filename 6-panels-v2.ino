boolean button1;
boolean button2;
boolean button3;

int lastState = 4;

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
  receive();
}

void remote(){
  receive();
  if(buttonAxis == 0){
    lastState = 1;
  }else if(button1 == 0){
    lastState = 2;
  }else if(button2 == 0){
    lastState = 3;
  }else if(button3 == 0){
    lastState = 4;
  }
  
  if(lastState == 1){
    customColor();
  }else if(lastState == 2){
    loadingLight();
  }else if(lastState == 3){
    turningLight();
  }else if(lastState == 4){
    whiteLight();
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
  if(yAxis == 0 && xAxis == 0){
    r = 255;
    g = 255;
    b = 255;
  }else if(yAxis < 6 && xAxis > 0){
    r = 0;
    g = 255;
    b = 150;
  }else if(yAxis > 6 && yAxis < 12 && xAxis > 0){
    r = 0;
    g = 255;
    b = 0;
  }else if(yAxis >= 12 && xAxis > 0){
    r = 255;
    g = 255;
    b = 0;
  }else if(yAxis >= 12 && xAxis < 0){
    r = 255;
    g = 170;
    b = 0;
  }else if(yAxis > 6 && yAxis < 12 && xAxis < 0){
    r = 255;
    g = 120;
    b = 0;
  }else if(yAxis < 6 && xAxis > 0){
    r = 255;
    g = 0;
    b = 0;
  }

  else if(yAxis < 6 && xAxis > 0){
    r = 255;
    g = 0;
    b = 255;
  }else if(yAxis > 6 && yAxis < 12 && xAxis > 0){
    r = 160;
    g = 0;
    b = 255;
  }else if(yAxis >= 12 && xAxis > 0){
    r = 0;
    g = 0;
    b = 255;
  }else if(yAxis >= 12 && xAxis < 0){
    r = 0;
    g = 130;
    b = 255;
  }else if(yAxis > 6 && yAxis < 12 && xAxis < 0){
    r = 0;
    g = 255;
    b = 255;
  }else if(yAxis < 6 && xAxis > 0){
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

void receive(){
  if(radio.available()){
    radio.read(&xAxis, sizeof(xAxis));
    radio.read(&yAxis, sizeof(yAxis));
    radio.read(&buttonAxis, sizeof(buttonAxis));

    Serial.print("X: ");
    Serial.print(xAxis);
    Serial.print("     Y: ");
    Serial.print(yAxis);
    Serial.print("     Button: ");
    Serial.println(buttonAxis);

    radio.read(&button1, sizeof(button1));
    radio.read(&button2, sizeof(button2));
    radio.read(&button3, sizeof(button3));

    Serial.print("B1: ");
    Serial.print(button1);
    Serial.print("     B2: ");
    Serial.print(button2);
    Serial.print("     B3: ");
    Serial.println(button3);

    radio.read(&brightness, sizeof(brightness));
    radio.read(&changingSpeed, sizeof(changingSpeed));

    Serial.print("bright: ");
    Serial.print(brightness);
    Serial.print("     speed: ");
    Serial.println(changingSpeed);
  }else{
    Serial.println("not available");
  }
  delay(500);
}