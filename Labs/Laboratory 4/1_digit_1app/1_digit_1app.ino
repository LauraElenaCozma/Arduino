const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int segSize = 8;
int index = 0;
int state = HIGH;

int segments[segSize] = {
  pinA , pinB , pinC , pinD , pinE , pinF , pinG , pinDP};
void setup() {
  for(int i = 0 ; i < segSize ; i++){
    pinMode(segments[i] , OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(segments[index] , state);
  index++;
  delay(500);
  if(index >= segSize)
  {
    index = 0;
    state = !state; 
  }
}
