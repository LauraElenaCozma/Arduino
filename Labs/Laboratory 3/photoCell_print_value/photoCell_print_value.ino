const int photoCellPin = A0;
const int ledPin = 13;

int photoCellValue = 0;
int ledState = 0;

int threshold = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(photoCellPin , INPUT);
  pinMode(ledPin , OUTPUT);
}
//the led lights up when pe put the finger on the photo cell
void loop() {
  // put your main code here, to run repeatedly:
  photoCellValue = analogRead(photoCellPin);
  Serial.println(photoCellValue);

  if(photoCellValue < threshold)
  {
    ledState = HIGH;
  }
  else ledState = LOW;

  digitalWrite(ledPin , ledState);
}
