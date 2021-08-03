#include "LedControl.h"
LedControl lc = LedControl(12 , 11 , 10 , 1); //DIN , CLK , LOAD , No of drivers

int matrixModel[][8] = {
  { 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0} , 
  { 1 , 2 , 0 , 0 , 0 , 0 , 0 , 0} , 
  { 0 , 0 , 1 , 1 , 1 , 0 , 1 , 2} , 
  { 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0} ,  
  { 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0} , 
  { 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0} , 
  { 0 , 1 , 0 , 0 , 0 , 2 , 1 , 1} , 
  { 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0}  
};


int gameOverMatrix[][8] = {
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} , 
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} 
};

int xValue = 0;
int yValue = 0;

bool joyMovedX = false;
bool joyMovedY = false;
int minThreshold= 200;
int maxThreshold= 900;

const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output
const int pinSW = A2;

int swState = LOW;
int lastSwState = LOW;
int switchValue;

unsigned long long currentTimePlayer = 0;
unsigned long long lastTimePlayer = 0;
int intervalBlinkPlayer = 100;
bool currentStatePlayer = 1;

int colPlayer = 5;
int rowPlayer = 7;
bool gameOver = 0;
void setup() {
  
  lc.shutdown(0 , false);//we have one driver, the driver no. 0
  lc.setIntensity(0 , 2);//intensity between 0 and 15
  lc.clearDisplay(0);
  pinMode(pinSW , INPUT_PULLUP);
}
void pushButton()
{
  swState = digitalRead(pinSW);

  if (swState !=  lastSwState) {
  if (swState == LOW) {
      gameOver = 0;
      colPlayer = 5;
      rowPlayer = 7;
  }
  }
  lastSwState = swState;
}
void moveJoystick()
{
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  int newColPlayer = colPlayer;
  int newRowPlayer = rowPlayer;

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMovedX = false;
  }

  if (xValue > maxThreshold && joyMovedX == false) {
    if(colPlayer > 0)
      newColPlayer = colPlayer - 1;
    else newColPlayer = 7;
    
    
    joyMovedX = true;
  }

  if (xValue < minThreshold && joyMovedX == false) {
    if(colPlayer < 7 )
      newColPlayer = colPlayer + 1;
    else newColPlayer = 0;
    joyMovedX = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedY = false;
  }

  if (yValue > maxThreshold && joyMovedY == false) {
    if(rowPlayer > 0)
      newRowPlayer = rowPlayer - 1;
    else newRowPlayer = 7;
    
    joyMovedY = true;
  }

  if (yValue < minThreshold && joyMovedY== false) {
    if(rowPlayer < 7)
      newRowPlayer = rowPlayer + 1;
    else newRowPlayer = 0;
    joyMovedY = true;
  }

  if(validateMove(newRowPlayer , newColPlayer) == 1){
    rowPlayer = newRowPlayer;
    colPlayer = newColPlayer;
  }
  else if(validateMove(newRowPlayer , newColPlayer) == -2){
    gameOver = true;
    rowPlayer = newRowPlayer;
    colPlayer = newColPlayer;
  }
  
}

int validateMove(int rowP , int colP)
{
  if(matrixModel[rowP][colP] == 0)
    return 1;
  else if(matrixModel[rowP][colP] == 1)
      return -1;//we have a wall. we cant move
      else return -2;//player died
}


void blinkPlayer()
{
  currentTimePlayer = millis();
  if(currentTimePlayer - lastTimePlayer >= intervalBlinkPlayer)
  {
    lastTimePlayer = currentTimePlayer;
    currentStatePlayer = !currentStatePlayer;
    lc.setLed(0 , 7 - colPlayer , rowPlayer , currentStatePlayer);
  }
}

unsigned long long currentTimeBomb = 0;
int intervalBlinkBomb = 400;

unsigned long long lastTimeBomb[][8] = {
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} 
};

void blinkBomb(int rowB , int colB)
{
  currentTimeBomb = millis();
  if(currentTimeBomb - lastTimeBomb[rowB][colB] >= intervalBlinkBomb)
  {
    lastTimeBomb[rowB][colB] = currentTimeBomb;
    if(matrixModel[rowB][colB] == 2)
    { 
      matrixModel[rowB][colB] = 3; //turn on
      lc.setLed(0 , 7 - colB , rowB , true);
    }

    else if(matrixModel[rowB][colB] == 3)
    { 
      matrixModel[rowB][colB] = 2; //turn off
      lc.setLed(0 , 7 -  colB , rowB , false);
    }
  }
}



void loop() {
  pushButton();
  if(gameOver == false){
    moveJoystick();
    for(int row = 0 ; row < 8 ; row++)
      for(int col = 0 ; col < 8 ; col++){
        if(matrixModel[row][col] >= 2)
           blinkBomb(row , col);
        else if(row == rowPlayer && col == colPlayer)
                blinkPlayer();
             else lc.setLed(0 , 7 - col , row , matrixModel[row][col]);//drive no, col, row, true - turns on the led 
    }
  }

  else{
    for(int row = 0 ; row < 8 ; row++)
      for(int col = 0 ; col < 8 ; col++){
        lc.setLed(0 , 7 - col , row , gameOverMatrix);
      }
  }
  

  
  
}
