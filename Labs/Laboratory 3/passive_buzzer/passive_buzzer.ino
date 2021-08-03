const int speakerPin = A0;
int speakerValue = 0;
void setup() {
  pinMode(speakerPin, INPUT);
Serial.begin(9600);
}
void loop() {
speakerValue = analogRead(speakerPin);
// let's print only if it read anything different than 0
if (speakerValue != 0)
Serial.println(speakerValue);
}
