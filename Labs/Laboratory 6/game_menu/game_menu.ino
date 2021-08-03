#include <LiquidCrystal.h>
#include <EEPROM.h>
const int RSPin = 8;
const int EPin = 9;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;

//variables used for eeprom
int eeAdress = 0;

LiquidCrystal lcd(RSPin , EPin , D4Pin , D5Pin , D6Pin , D7Pin);
struct Position 
{
  int col , row;
};
int currentCursorPosition = 0;
const int noOfOptions = 3;
Position pos[noOfOptions] = {
  {0 , 0} , {6 , 0} , {3 , 1}  //the position of the >
};

int modifyStartScreen = 0; //=0 we are in the main menu; =1 we are in the menu that shows current level and score; =2 we are in the menu that shows "Game finished!"
int modifyHighScoreScreen = 0;  //=0 we are in the main menu; =1 we are in the menu that shows the high score
int modifySettingsScreen = 0;   //=0 we are in the main menu; =1 we are in the menu that shows the name of the user
int mainMenuScreen = 1; //=0 if we aren't in the main menu; =1 if we are

//initialize the joystick
const int buttonPin= A2; // digital pin connected to switch output
const int xPin = A0; // A0 - analog pin connected to X output
const int yPin = A1; // A1 - analog pin connected to Y outputconst int pinSW = 10; // digital pin connected to switch output

int xValue = 0;
int yValue = 0;
bool joyMovedX = false;
bool joyMovedY = false;
int minThreshold= 100;
int maxThreshold= 900;



String username = "LAURA    ";
const int noOfUsernamePos = 9;
int currentStringPos = 0;


void setupName()
{
      //function that sets the username in settings menu
      xValue = analogRead(xPin);
      
      if (modifySettingsScreen == 1 && xValue >= minThreshold && xValue <= maxThreshold) {
          joyMovedX = false;
      }
  
      if (modifySettingsScreen == 1 && xValue < minThreshold && joyMovedX == false) {
        if(currentStringPos > 0)
          currentStringPos --;
        else currentStringPos = noOfUsernamePos - 1;
        joyMovedX = true;
      }
    
      if (modifySettingsScreen == 1 && xValue > maxThreshold && joyMovedX == false) {
        if(currentStringPos < noOfUsernamePos - 1)
          currentStringPos ++;
        else currentStringPos = 0;
        joyMovedX = true;
      }
       
      

      
      yValue = analogRead(yPin);
      if (modifySettingsScreen == 1 && yValue >= minThreshold && yValue <= maxThreshold) {
          joyMovedY = false;
      }
  
      if (modifySettingsScreen == 1 && yValue < minThreshold && joyMovedY == false) {
        if(username[currentStringPos]  > 'A' && username[currentStringPos] <= 'Z' )
          username[currentStringPos] --;
        else if(username[currentStringPos] == 'A')username[currentStringPos] = ' '; 
        else if(username[currentStringPos] == ' ')username[currentStringPos] = 'Z';
        joyMovedY = true;
      }
    
      if (modifySettingsScreen == 1 && yValue > maxThreshold && joyMovedY == false) {
        if(username[currentStringPos] >= 'A' && username[currentStringPos] < 'Z')
          username[currentStringPos] ++;
        else if(username[currentStringPos] == 'Z')username[currentStringPos] = ' '; 
        else if(username[currentStringPos] == ' ')username[currentStringPos] = 'A';
        joyMovedY = true;
      }

      
}


void joystickMovesX()
{
  //function that controlls the selected option in main menu
  xValue = analogRead(xPin);

  // On Ox axis, if the value is bigger than a chosen max threshold, then
  // move the cursor
  if (mainMenuScreen == 1 && xValue < minThreshold && joyMovedX == false) {
  if (currentCursorPosition > 0) {
      currentCursorPosition--;
  } 
  else {
      currentCursorPosition = noOfOptions - 1;
  }
  joyMovedX = true;
  lcd.clear();
  mainMenu();
  lcd.setCursor(pos[currentCursorPosition].col , pos[currentCursorPosition].row);
  lcd.print(">");
  }

  if (mainMenuScreen == 1 && xValue > maxThreshold && joyMovedX == false) {
  if (currentCursorPosition < noOfOptions - 1) {
      currentCursorPosition ++;
  } 
  else {
      currentCursorPosition = 0;
  }
  joyMovedX = true;
  lcd.clear();
  mainMenu();
  lcd.setCursor(pos[currentCursorPosition].col , pos[currentCursorPosition].row);
  lcd.print(">");

  }

  
  if (mainMenuScreen == 1 && xValue >= minThreshold && xValue <= maxThreshold) {
  joyMovedX = false;
  }
}


void mainMenu()
{
  //function that prints the options of the main menu
  lcd.setCursor(1 , 0);
  lcd.print("Start");
  lcd.setCursor(7 , 0);
  lcd.print("HighScore");
  lcd.setCursor(4 , 1);
  lcd.print("Settings");
}



unsigned int currentTime = 0;
unsigned int lastLevelTime = 0;
unsigned int lastFinishedTime = 0;

int startingLevelValue = 0;
int noOfLives = 3;
int score = 0;
int maxScore = 0;

int buttonState = LOW;
int lastButtonState = LOW;
bool pressedButton = false;//default is not pressed

void levelMenu()
{
  //function that prints the options of the level menu
  lcd.setCursor(0 , 0);
  lcd.print("Lives:");
  lcd.print(noOfLives);
  lcd.setCursor(8 , 0);
  lcd.print("Level:");
  lcd.print(startingLevelValue);
  lcd.setCursor(4 , 1);
  lcd.print("Score:");
  lcd.print(score);
}



void finishedGameMenu()
{
  //function that prints the options of the finished game menu
  lcd.setCursor(1 , 0);
  lcd.print("Game finished!");
  lcd.setCursor(5 , 1);
  lcd.print(">Exit");

  buttonState = digitalRead(buttonPin);
  if (buttonState !=  lastButtonState) {
  if (buttonState == LOW) {//button was pressed 2nd time to exit this menu
     if(currentCursorPosition == 0 && modifyStartScreen == 2) //we are in the start menu, 2nd option(game finished)
     {
      modifyStartScreen = 0;
      mainMenuScreen = 1;
      lcd.clear();
      lcd.print(">");
      mainMenu();
      
      
     } 
  }
  lastButtonState = buttonState;
  }
  

  
} 

void highScoreMenu()
{
  //function that controlls the selected option of high score menu
  lcd.setCursor(0 , 0);
  lcd.print("The highScore is ");
  lcd.setCursor(0 , 1);
  EEPROM.get(eeAdress , maxScore);
  lcd.print(maxScore);
  lcd.setCursor(7 , 1);
  lcd.print(">Exit");

  buttonState = digitalRead(buttonPin);
  if (buttonState !=  lastButtonState) {
  if (buttonState == LOW) {//button was pressed
     if(currentCursorPosition == 1 && modifyHighScoreScreen == 1)
     {
      modifyHighScoreScreen = 0;
      lcd.clear();
      lcd.print(">");
      mainMenu();
      mainMenuScreen = 1;
      currentCursorPosition = 0;

       
     } 
  }
  lastButtonState = buttonState;
  }
  
}
const int noOfSetPos = 3;
Position setPos[noOfSetPos] = {
  {0 , 0} , {0 , 1} , {11, 1}
};
int currentSetPos = 0;

int firstInSettings = 1; //to print only the first time the > in front of lev
int buttonPressedSettings = 0; // 0 = not pressed; 1 = pressed at name; 2 = pressed at level; 3 = pressed at exit

void printSettingsMenu()
{
    //function that prints the options of the settings menu
    lcd.setCursor(1 , 0);
    lcd.print("Name:");
    lcd.print(username);
    lcd.setCursor(1 , 1);
    lcd.print("Lev:");
    lcd.setCursor(6 , 1);
    lcd.print(" ");
    lcd.setCursor(5 , 1);
    lcd.print(startingLevelValue);
    lcd.setCursor(12 , 1);
    lcd.print("Exit");

    if(buttonPressedSettings == 1) //the name is editing
    {
      lcd.setCursor(currentStringPos + 6 , 0);
      lcd.print(" ");
      delay(6 );
      
    }
     
}


void settingsMenu()
{
  //function that controlls the selected option of settings menu
  printSettingsMenu();

  if(buttonPressedSettings == 0)
  {
    xValue = analogRead(xPin);
    if (modifySettingsScreen == 1 && xValue >= minThreshold && xValue <= maxThreshold) {
      joyMovedX = false;
    }

    if (modifySettingsScreen == 1 && xValue < minThreshold && joyMovedX == false) { //we want to move between name level and exit
      
      if(currentSetPos > 0)currentSetPos --;
      else currentSetPos = noOfSetPos - 1;
      joyMovedX = true;
      Serial.println(currentSetPos);
      lcd.clear();
      printSettingsMenu();
      lcd.setCursor(setPos[currentSetPos].col , setPos[currentSetPos].row);
      lcd.print(">");
    }

    if(modifySettingsScreen == 1 && xValue > maxThreshold && joyMovedX == false){
       
      if(currentSetPos < noOfSetPos - 1)currentSetPos ++;
      else currentSetPos = 0;
      joyMovedX = true;
      Serial.println(currentSetPos);
      lcd.clear();
      printSettingsMenu();
      lcd.setCursor(setPos[currentSetPos].col , setPos[currentSetPos].row);
      lcd.print(">");
    }
  } 
  

    buttonState = digitalRead(buttonPin);
    if (buttonState !=  lastButtonState) {
    if (buttonState == LOW) {//button was pressed
      if(modifySettingsScreen == 1 && buttonPressedSettings == 0 && currentCursorPosition == 2)//we are in settings
      {
        switch(currentSetPos)
        {
          case 0: buttonPressedSettings = 1;//we want to modify the name
                  break;
          case 1: buttonPressedSettings = 2;//we want to modify the level
                  break;
          case 2: buttonPressedSettings = 3;//we want to exit
                  break;
        }
      }
      else if(modifySettingsScreen == 1 && currentCursorPosition == 2 && buttonPressedSettings != 0)
        buttonPressedSettings = 0;
        currentStringPos = 0;
  
    }
    lastButtonState = buttonState;
  }
  
  if(buttonPressedSettings == 3)
  {
       modifySettingsScreen = 0;
       lcd.clear();
       lcd.print(">");
       mainMenu();
       mainMenuScreen = 1;
       currentCursorPosition = 0;
       currentSetPos = 0;
       firstInSettings = 1;
       currentStringPos = 0;
       buttonPressedSettings = 0;
  }
  if(buttonPressedSettings == 2)
  {
      yValue = analogRead(yPin);
      if (modifySettingsScreen == 1 && yValue >= minThreshold && yValue <= maxThreshold) {
          joyMovedY = false;
      }
  
      if (modifySettingsScreen == 1 && yValue < minThreshold && joyMovedY == false) {
      if (startingLevelValue > 0) {
          startingLevelValue--;
      } 
      else {
          startingLevelValue = 30; //max levels 30
      }
      joyMovedY = true;
      
      }
    
      if (modifySettingsScreen == 1 && yValue > maxThreshold && joyMovedY == false) {
      if (startingLevelValue < 30) {
          startingLevelValue ++;
      } 
      else {
          startingLevelValue = 0;
      }
      joyMovedY = true;
      }
  }
  if(buttonPressedSettings == 1)
  {
      setupName();
  }
  
}


void buttonPressed()
{
  //function that check if the button was pressed or the joystick was moved to left or right if we are in the main menu(in order to select an option)
  if(mainMenuScreen == 1)
  {
    buttonState = digitalRead(buttonPin);
    if (buttonState !=  lastButtonState) {
    if (buttonState == LOW) {//button was pressed
      pressedButton = true;
       
    }
    lastButtonState = buttonState;
    }
    yValue = analogRead(yPin);
    if (mainMenuScreen == 1 && yValue >= minThreshold && yValue <= maxThreshold) {
      joyMovedY = false;
    }
    if (mainMenuScreen == 1 && ((yValue < minThreshold && joyMovedY == false) || (yValue > maxThreshold && joyMovedY == false) || pressedButton == true)) { //we want to change the category
      lastButtonState = LOW;
      pressedButton = false;
      if(currentCursorPosition == 0) 
      {
        modifyStartScreen = 1;
        lastLevelTime = millis();
        lastFinishedTime = millis();
        lcd.clear(); 
        mainMenuScreen = 0;
      } 
      if(currentCursorPosition == 1)
      {
          lcd.clear();
          mainMenuScreen = 0;
          modifyHighScoreScreen = 1;
      }
      if(currentCursorPosition == 2)
      {
        lcd.clear();
        mainMenuScreen = 0;
        modifySettingsScreen = 1;
      }
    joyMovedY = true;

  }

  }
  
  
}

void screenTransition()
{
  //function that calls the functions of the current type of menu
  if(modifyStartScreen == 1){
        levelMenu();
        currentTime = millis();

        if(currentTime - lastLevelTime >=2000)
        {
          startingLevelValue ++;
          score = 3 * startingLevelValue;
          lastLevelTime = currentTime;
        }

        if(currentTime - lastFinishedTime >=10000)
        {
          modifyStartScreen = 2;
          lastFinishedTime = currentTime;
          startingLevelValue = 0;
          EEPROM.get(eeAdress , maxScore);
          if(score > maxScore) maxScore = score;
          EEPROM.put(eeAdress , maxScore);
          score = 0;
          lcd.clear();
           
        }
  }

  if(modifyStartScreen == 2){
    
        finishedGameMenu();
  }

  if(modifyHighScoreScreen == 1)
  {
        highScoreMenu();
  }

  if(modifySettingsScreen == 1)
  {
      if(firstInSettings == 1) //to print only the first time the > in front of lev
      {
        lcd.setCursor(0 , 0);
        lcd.print(">");
        firstInSettings = 0;
      }
      printSettingsMenu();
      settingsMenu();
      
  }
  
}




void setup() {

  pinMode(buttonPin , INPUT_PULLUP);
  lcd.begin(16 , 2); //number of columns and 2 rows
  lcd.print(">");
  mainMenu();
  Serial.begin(9600);
}

void loop() {
  Serial.println(xValue);
  joystickMovesX();
  buttonPressed();
  screenTransition();
  
}
