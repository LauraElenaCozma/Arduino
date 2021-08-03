int xValue = 0;
int yValue = 0;
int buttonValue = 0;

const int pinX = A0;
const int pinY = A1;
const int pushButton = 10;
void setup() {
  // put your setup code here, to run once:
  /*pinMode(pinX , INPUT); we dont need to set this because they are always analog input
  pinMode(pinY , INPUT);*/
  pinMode(pushButton ,INPUT_PULLUP); //so the default value of the push button is 1
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  buttonValue = digitalRead(pushButton);
  Serial.print("Switch: ");
  Serial.print(buttonValue);
  Serial.print("  |  ");
  Serial.print("X Axis ");
  Serial.print(xValue);
  Serial.print("  |  ");
  Serial.print("Y Axis ");
  Serial.println(yValue);
  delay(300); //to see the values
}
