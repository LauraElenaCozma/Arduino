const int pushButton = 2;
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pushButton , INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(pushButton);
  buttonState = !buttonState;
  if(buttonState == HIGH)
  {
    counter++;
    Serial.println(counter);
  }

  
}
