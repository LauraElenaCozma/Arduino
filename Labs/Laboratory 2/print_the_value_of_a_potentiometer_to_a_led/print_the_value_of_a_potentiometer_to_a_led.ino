int potVal = 0;
int potPin = A0;
int ledPin = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin , OUTPUT);
  pinMode(potPin , INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  potVal = map(potVal , 0 , 1023 , 0 , 255);
  analogWrite(ledPin , potVal);
}
