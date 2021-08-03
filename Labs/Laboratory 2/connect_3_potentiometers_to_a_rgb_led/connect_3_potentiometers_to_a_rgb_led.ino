const int potPinRed = A0;
const int potPinGreen = A1;
const int potPinBlue = A2;

const int ledPinRed = 9;
const int ledPinGreen = 10;
const int ledPinBlue = 11;

int potValueRed = 0;
int potValueGreen = 0;
int potValueBlue = 0;

int ledValueRed = 0;
int ledValueGreen = 0;
int ledValueBlue = 0;

void setup() {
  
  pinMode(potPinRed , INPUT);
  pinMode(potPinGreen , INPUT);
  pinMode(potPinBlue , INPUT);
  
  pinMode(ledPinRed , OUTPUT);
  pinMode(ledPinGreen , OUTPUT);
  pinMode(ledPinBlue , OUTPUT);
}

void setColor(){

  //function that reads the value from each potentiometer, maps the values for analog output and set the color to the led through analogWrite
  potValueRed = analogRead(potPinRed);
  ledValueRed = map(potValueRed , 0 , 1023 , 0 , 255);

  analogWrite(ledPinRed , ledValueRed);
  
  potValueGreen = analogRead(potPinGreen);
  ledValueGreen = map(potValueGreen , 0 , 1023 , 0 , 255);

  analogWrite(ledPinGreen , ledValueGreen);
  
  potValueBlue = analogRead(potPinBlue);
  ledValueBlue = map(potValueBlue , 0 , 1023 , 0 , 255);

  analogWrite(ledPinBlue , ledValueBlue);
}

void loop() {
  setColor();
}
