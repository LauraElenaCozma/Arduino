const int buzzerPin = 11;
int buzzerTone = 1000;
void setup() {
}
void loop() {
tone(buzzerPin, buzzerTone);
delay(1000);
noTone(buzzerPin);

buzzerTone += 50;
tone(buzzerPin, buzzerTone);
delay(1000);
noTone(buzzerPin);

buzzerTone -= 50;
}
