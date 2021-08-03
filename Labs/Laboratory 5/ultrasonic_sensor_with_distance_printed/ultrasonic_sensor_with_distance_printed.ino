#include <LiquidCrystal.h>
const int RSPin = 12;
const int EPin = 11;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;
const int trigPin = 9;
const int echoPin = 10;

long duration;
long distance;

LiquidCrystal lcd(RSPin , EPin , D4Pin , D5Pin , D6Pin , D7Pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  Serial.begin(9600);
  lcd.begin(16 , 2); //number of columns and 2 rows
  lcd.print("DISTANCE:");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin , LOW); //to clear 
  delayMicroseconds(2);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);//the sound is emitted for 10 micro sec
  digitalWrite(trigPin , LOW);//we turn it off
  duration = pulseIn(echoPin , HIGH);  //pulse in returns the time. pulseIn gives the time between trig being high and low
  distance = duration * 0.034 / 2;
  /*Serial.print("Distance: ");
  Serial.println(distance);*/
  lcd.setCursor(0,0);
  
  lcd.setCursor(0 , 1);
  lcd.print(distance);
  lcd.print("                         ");
  delay(10);
  //lcd.clear( );
}
