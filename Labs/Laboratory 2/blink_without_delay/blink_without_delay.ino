const int ledPin = 12;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
const int interval = 1000;
int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin , OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
   currentTime = millis();
  Serial.println(currentTime);
  
  if(currentTime - lastTime >= interval)
  {
    ledState = !ledState;
    digitalWrite(ledPin , ledState);
    lastTime = currentTime;
  }

}
