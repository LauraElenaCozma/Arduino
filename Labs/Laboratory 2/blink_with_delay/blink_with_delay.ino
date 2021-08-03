const int LedPin = 12;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedPin , HIGH);
  delay(2500);
  digitalWrite(LedPin , LOW);
  delay(1000);
}
