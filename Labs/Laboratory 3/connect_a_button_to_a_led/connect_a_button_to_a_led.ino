const int pushButton = 2;
const int ledPin = 13;
int ledState;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton , INPUT_PULLUP);
  pinMode(ledPin , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  ledState = !buttonState;   //pentru ca am circuitul avea default 1 la buton si voiam ca atunci cand nu e apasat butonul, ledul sa fie stins
  digitalWrite(ledPin , ledState);
}
