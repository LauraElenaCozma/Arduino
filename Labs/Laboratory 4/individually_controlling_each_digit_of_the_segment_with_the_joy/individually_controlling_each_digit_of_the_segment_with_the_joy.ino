//declare all the segments pins
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;




// declare all the joystick pins
const int pinSW = A2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output


//variables used for joystick
bool joyMovedX = false;
bool joyMovedY = false;

int minThreshold = 400;
int maxThreshold = 600;

int switchValue = 0;
int xValue = 0;
int yValue = 0;

int swState = HIGH; 
int lastSwState = HIGH;

const int segSize = 8; //number of segments used to light a digit including the decimal point
// segments array
int segments[segSize] = {
  pinA , pinB , pinC , pinD , pinE , pinF , pinG , pinDP
};

const int noOfDisplays = 4;
// digits array, to switch between them easily
int digits[noOfDisplays] = {
  pinD1 , pinD2 , pinD3 , pinD4
 };   

const int noOfDigits = 10;
byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

//array that contains the digits displayed 
int currentNumber[noOfDisplays] = {
  0 , 0 , 0 , 0
};

//write the digit received as parameter and also the value of the decimal point(low or high)
void displayNumber(byte digit , byte decimalPoint) {
  for (int i = 0 ; i < segSize - 1 ; i++) {
  digitalWrite(segments[i] , digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1] , decimalPoint);
}

// activate the display no. received as param; which digit we want to light up
void showDigit(int num) {
  for (int i = 0 ; i < noOfDisplays ; i++) {
  digitalWrite(digits[i] , HIGH);
  }
  digitalWrite(digits[num] , LOW);
}


int dpState = HIGH ;


void setup() {
  //activates all the segments of a digit as an output
  for (int i = 0 ; i < segSize ; i++){
    pinMode(segments[i], OUTPUT);  
  }
  //activates all the digit as an output
  for (int i = 0; i < noOfDisplays; i++)
  {
  pinMode(digits[i], OUTPUT);  
  }
  //the button of the joystick is an input
  pinMode(pinSW , INPUT_PULLUP);

  Serial.begin(9600);
}

int currentPosition = 0; //which digit we write at the current moment

void loop() {

  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swState = digitalRead(pinSW);
  
  if(swState != lastSwState)
     if(swState == LOW) // if the joystick Button is pressed 
        dpState = !dpState;
  
  lastSwState = swState;
  
        for(int i=0 ; i <noOfDisplays ; i++) 
      if(i != currentPosition){
        
         showDigit(i); // lights up the i th display
         displayNumber(currentNumber[i] , LOW); // print the digit. the dp led is not lighted up
         delay(5);
        }
      else {
        
        showDigit(currentPosition);
        displayNumber(currentNumber[currentPosition] , dpState);
        delay(5);
        } 
      
  if(xValue < minThreshold && joyMovedX == false && dpState == HIGH){
    if (currentPosition > 0) {
      currentPosition--;
    } 
    else {
      currentPosition = 3;
    }
    joyMovedX = true;
  }
  
  if(xValue > maxThreshold && joyMovedX == false && dpState == HIGH){
    if (currentPosition < 3) {
      currentPosition++;
    } 
    else {
      currentPosition = 0;
    }
    joyMovedX = true;
  }
  
  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMovedX = false;
  }
  
  
  
  
  
  // On OY axis, if the value is lower than a chosen min threshold, then de1/crease by 1 the digit value
  if (yValue < minThreshold && joyMovedY == false && dpState == LOW) {
    if (currentNumber[currentPosition] > 0) {
       currentNumber[currentPosition]--;
    } 
    else {
       currentNumber[currentPosition] = 9;
    }
    joyMovedY = true;
    }
    // On OY axis, if the value is bigger than a chosen max threshold, then increase by 1 the digit value
  if (yValue > maxThreshold && joyMovedY == false && dpState == LOW) {
    if (currentNumber[currentPosition] < 9) {
      currentNumber[currentPosition]++;
    } 
    else {
      currentNumber[currentPosition] = 0;
    }
    joyMovedY = true;
  }
  
  
  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedY = false;
  }
  
}
