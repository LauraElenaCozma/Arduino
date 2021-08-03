const int speakerPin = A0;
const int ledPin = 13;
int speakerValue = 0;
int ledState = 0;
// set the sensitivity
const int threshold = 5;

void setup() {
pinMode(speakerPin, INPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}
void loop() {
speakerValue = analogRead(speakerPin);
if (speakerValue != 0)
Serial.println(speakerValue);
if (speakerValue > threshold) {
Serial.println("Knock");
ledState = !ledState;
digitalWrite(ledPin, ledState);
}
delay(10);
}
