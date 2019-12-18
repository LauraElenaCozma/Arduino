#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
LedControl lc = LedControl(12 , 11 , 10 , 1); //DIN , CLK , LOAD , No of drivers
const int RSPin = 8;
const int EPin = 9;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;
const int buzzPin = A3;
const int rowComp[] = {6 , 11 , A5 , 9 , 5 , A4 , 4 , A2};  //C1 C2 C3 C4  C5 C6  C7  C8 - anodes
const int colComp[] = {10 , 3 , 2 , 7 , A3 , 8 , 12 , 13};
const int redLedPin = 6;
const int greenLedPin = 7;
int swState = LOW;
int lastSwState = LOW;
int switchValue;

int xValue = 0;

bool joyMovedX = false;

int colPlayer = 1;
int rowPlayer = 5;

bool gameOver = 0;

const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output
const int pinSW = A2;

//variables used for eeprom
int eeAdress = 0;
unsigned long long timeWhenGameStarted = 0;

LiquidCrystal lcd(RSPin , EPin , D4Pin , D5Pin , D6Pin , D7Pin);
struct Position
{
  int col , row;
};
int currentCursorPosition = 0;
const int noOfOptions = 4;
Position pos[noOfOptions] = {
  {0 , 0} , {6 , 0} , {0 , 1} , {11 , 1} //the position of the > in the main menu
};

int modifyStartScreen = 0; //=0 we are in the main menu; =1 we are in the menu that shows current level and score; =2 we are in the menu that shows "Game finished!" =3 we are in the manu that shows difficulty
int modifyHighScoreScreen = 0;  //=0 we are in the main menu; =1 we are in the menu that shows the high score
int modifySettingsScreen = 0;   //=0 we are in the main menu; =1 we are in the menu that shows the name of the user
int modifyInfoScreen = 0;  //=0 is we are not in the info section; =1 if we are
int mainMenuScreen = 1; //=0 if we aren't in the main menu; =1 if we are

//initialize the joystick
const int buttonPin= A2; // digital pin connected to switch output
const int xPin = A0; // A0 - analog pin connected to X output
const int yPin = A1; // A1 - analog pin connected to Y outputconst int pinSW = 10; // digital pin connected to switch output

int xValueMenu = 0;
int yValue = 0;
bool joyMovedXMenu = false;
bool joyMovedY = false;
int minThreshold= 100;
int maxThreshold= 900;


unsigned long long currentTime = 0;
unsigned long long lastFinishedTime = 0;

String username = "PLAYER ";
const unsigned int noOfUsernamePos = 7;
int currentStringPos = 0;

int startingLevelValue = 0;
int noOfLives = 3;
int score = 0;
int maxScore;
String maxUsername = "";

int buttonState = LOW;
int lastButtonState = LOW;
bool pressedButton = false;//default is not pressed




bool pressedStart = 0;

int currentColWalls = 0;
unsigned long long lastTimeScrollWalls = 0;

unsigned long long lastTimeBlinkPlayer = 0;
bool stateBlinkPlayer = 1;

unsigned long long  lastTime = 0;
int currentColIntroInGame = 0;
int intervalScrollingIntro = 500;

bool display321 = 0;
int indexStartPath = 2; //the index where the path starts 
int randNumber = 7;

unsigned int speedPlayer;
unsigned int speedEasy = 600;
unsigned int speedMedium = 400;
unsigned int speedHard = 300;
unsigned int valueMultiplyScore;
unsigned int valueMultiplyScoreEasy = 1;
unsigned int valueMultiplyScoreMedium = 2;
unsigned int valueMultiplyScoreHard = 3;

unsigned long long lastTimeExtraLifeGenerated = 0;
bool firstLifeGenerated = false;
bool secondLifeGenerated = false;
bool thirdLifeGenerated = false;
bool increment1 = false;
bool increment2 = false;
bool increment3 = false;

bool freezeNoTone = false; //when we are freezed no tone is accepted
bool secondLevel = false;
bool thirdLevel = false;

const PROGMEM bool oneMatrix[][8] = {
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 1 , 1 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 1 , 1 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} 
};

const PROGMEM bool twoMatrix[][8] = {
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 0 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 0 , 0 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 0 , 0 , 0 , 0} ,
  {0 , 1 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 1 , 1 , 1 , 1 , 1 , 0 , 0} 
};

const PROGMEM bool threeMatrix[][8] = {
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 0 , 0 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 0 , 0 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} ,
  {0 , 0 , 1 , 1 , 1 , 1 , 0 , 0} 
};

const PROGMEM bool happyFace[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 0 , 1 , 1 , 0 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 0 , 1 , 1 , 0 , 1 , 1} ,
  {1 , 1 , 1 , 0 , 0 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} 
};

const PROGMEM bool sadFace[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 0 , 1 , 1 , 0 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} ,
  {1 , 1 , 1 , 0 , 0 , 1 , 1 , 1} ,
  {1 , 1 , 0 , 1 , 1 , 0 , 1 , 1} ,
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1} 
};

bool walls[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  {1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } 
};

const PROGMEM bool patternWallsEasy[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 0 , 1 } ,
  {1 , 1 , 1 , 1 , 1 , 0 , 0 , 1 } , 
  {0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 } , 
  {1 , 0 , 1 , 0 , 1 , 1 , 1 , 1 } , 
  {1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 } 
};

const PROGMEM bool patternWallsMedium[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  {1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 } , 
  {0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 } , 
  {1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } 
};

const PROGMEM bool patternWallsHard[][8] = {
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ,
  {1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 } , 
  {0 , 0 , 0 , 0 , 1 , 1 , 0 , 1 } , 
  {1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 } , 
  {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } 
};

int gameDifficulty = 0; //1 - easy. 2 medium. 3 hard
int widthOfPath = 0; //3 for medium and hard. 4 for easy


///variables used for the welcome message at the beginning of the game
const PROGMEM bool welcomeMatrix[][45] = {
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0} ,
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0},
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0},
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0},
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0},
  {0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0},
  {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0}
 
};
bool printedWelcome = 0;
unsigned long long lastTimeWelcome = 0;
int currentColWelcome = 0;

//variables used for moving the player
int yValuePlayer = 0;
bool joyMovedYPlayer = false;

///variables used to display start game
const int noOfRowsIntroInGame = 8;
const int noOfColumnsIntroInGame = 62;
bool introInGameMatrix[noOfRowsIntroInGame][noOfColumnsIntroInGame] = {
{0, 0, 0, 0, 0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0 , 0,   0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0 ,   0,  0, 0, 0,  0 , 0,  0, 0, 0, 0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0  , 0,   0, 0, 0, 0    , 0,   0, 0, 0   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   0, 1, 1, 1 ,   0,   1, 1, 1, 1 , 1,   0,   0, 1, 1, 0 ,   0,   1, 1, 1, 0 ,   0,  1, 1, 1,  1 , 1,  0, 0, 0, 0,   0, 1, 1, 0 ,   0,   0, 1, 1, 0  , 0,   1, 0, 0, 1    , 0,   1, 1, 1   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   1, 0, 0, 0 ,   0,   0, 0, 1, 0 , 0,   0,   1, 0, 0, 1 ,   0,   1, 0, 0, 1 ,   0,  0, 0, 1,  0 , 0,  0, 0, 0, 0,   1, 0, 0, 1 ,   0,   1, 0, 0, 1  , 0,   1, 1, 1, 1    , 0,   1, 0, 0   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   0, 1, 0, 0 ,   0,   0, 0, 1, 0 , 0,   0,   1, 0, 0, 1 ,   0,   1, 1, 1, 0 ,   0,  0, 0, 1,  0 , 0,  0, 0, 0, 0,   1, 0, 0, 0 ,   0,   1, 0, 0, 1  , 0,   1, 1, 1, 1    , 0,   1, 1, 1   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   0, 0, 1, 0 ,   0,   0, 0, 1, 0 , 0,   0,   1, 1, 1, 1 ,   0,   1, 0, 1, 0 ,   0,  0, 0, 1,  0 , 0,  0, 0, 0, 0,   1, 0, 1, 1 ,   0,   1, 1, 1, 1  , 0,   1, 0, 0, 1    , 0,   1, 0, 0   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   0, 0, 0, 1 ,   0,   0, 0, 1, 0 , 0,   0,   1, 0, 0, 1 ,   0,   1, 0, 1, 0 ,   0,  0, 0, 1,  0 , 0,  0, 0, 0, 0,   1, 0, 0, 1 ,   0,   1, 0, 0, 1  , 0,   1, 0, 0, 1    , 0,   1, 0, 0   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   1, 1, 1, 0 ,   0,   0, 0, 1, 0 , 0,   0,   1, 0, 0, 1 ,   0,   1, 0, 0, 1 ,   0,  0, 0, 1,  0 , 0,  0, 0, 0, 0,   0, 1, 1, 0 ,   0,   1, 0, 0, 1  , 0,   1, 0, 0, 1    , 0,   1, 1, 1   , 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0 , 0,   0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0 ,   0,  0, 0, 0,  0 , 0,  0, 0, 0, 0,   0, 0, 0, 0 ,   0,   0, 0, 0, 0  , 0,   0, 0, 0, 0    , 0,   0, 0, 0   , 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

//variables used for the difficulty menu
bool buttonPressedDifficulty = 0;
Position difficultyPosition[] = {
  {0 , 0} , {8 , 0} , {5 , 1}
};
int cursorDifficultyPosition = 0;
int firstInDifficulty = 1; //variable used for the first time when we are in difficulty menu to print > before easy

//variables for try again
Position tryAgainPosition[] = {
  {0 , 0} , {0 , 1}
}; 
//the first one for try again
//the second one for exit
int cursorTryAgainPosition = 0;
bool firstInTryAgain = 1;
bool buttonPressedTryAgain = 0;

void displayMatrix(const PROGMEM bool m[][8])
{
  //prints a 8*8 matrix on the matrix
  for(int row = 0 ; row < 8 ; row++)
    {for(int col = 0 ; col < 8 ; col++)
    {
      bool val = pgm_read_byte_near(m[row] + col);
      Serial.print(val);
      Serial.print(" ");
      lc.setLed(0 , 7 - col , row , val);
    }Serial.println(" ");}
     Serial.println(" ");   
}

void display321BeforeStart()
{
  displayMatrix(threeMatrix);
  delay(1000); //it is used to display the numbers before starting the game. does not affect the game
  displayMatrix(twoMatrix);
  delay(1000);
  displayMatrix(oneMatrix);
  delay(1000);
  display321 = 1;
}

void setupName()
{
      //function that sets the username in settings menu
      xValueMenu = analogRead(xPin);
      
      if (modifySettingsScreen == 1 && xValueMenu >= minThreshold && xValueMenu <= maxThreshold) {
          joyMovedXMenu = false;
      }
  
      if (modifySettingsScreen == 1 && xValueMenu < minThreshold && joyMovedXMenu == false) {
        if(username[currentStringPos] >= 'A' && username[currentStringPos] < 'Z')
          username[currentStringPos] ++;
        else if(username[currentStringPos] == 'Z')username[currentStringPos] = ' '; 
        else if(username[currentStringPos] == ' ')username[currentStringPos] = 'A';
        joyMovedXMenu = true;
      }
    
      if (modifySettingsScreen == 1 && xValueMenu > maxThreshold && joyMovedXMenu == false) {
        if(username[currentStringPos]  > 'A' && username[currentStringPos] <= 'Z' )
          username[currentStringPos] --;
        else if(username[currentStringPos] == 'A')username[currentStringPos] = ' '; 
        else if(username[currentStringPos] == ' ')username[currentStringPos] = 'Z';
        joyMovedXMenu = true;
      }
       
      

      
      yValue = analogRead(yPin);
      if (modifySettingsScreen == 1 && yValue >= minThreshold && yValue <= maxThreshold) {
          joyMovedY = false;
      }
  
      if (modifySettingsScreen == 1 && yValue < minThreshold && joyMovedY == false) {
        if(currentStringPos < noOfUsernamePos - 1)
          currentStringPos ++;
        else currentStringPos = 0;
        joyMovedY = true;
      }
    
      if (modifySettingsScreen == 1 && yValue > maxThreshold && joyMovedY == false) {
        if(currentStringPos > 0)
          currentStringPos --;
        else currentStringPos = noOfUsernamePos - 1;
        joyMovedY = true;
      }

      
}


void selectOptionMainMenu()
{
  //function that controlls the selected option in main menu
  yValue = analogRead(yPin);

  // On Ox axis, if the value is bigger than a chosen max threshold, then
  // move the cursor
  if (mainMenuScreen == 1 && yValue < minThreshold && joyMovedY == false) {
    if (currentCursorPosition < noOfOptions - 1) {
        currentCursorPosition ++;
    } 
    else currentCursorPosition = 0;
    joyMovedY = true;
    lcd.clear();
    mainMenu();
    lcd.setCursor(pos[currentCursorPosition].col , pos[currentCursorPosition].row);
    lcd.print(">");
  }

  if (mainMenuScreen == 1 && yValue > maxThreshold && joyMovedY == false) {
    if (currentCursorPosition > 0) {
        currentCursorPosition--;
    } 
    else currentCursorPosition = noOfOptions - 1;
    joyMovedY = true;
    lcd.clear();
    mainMenu();
    lcd.setCursor(pos[currentCursorPosition].col , pos[currentCursorPosition].row);
    lcd.print(">");

  }

  
  if (mainMenuScreen == 1 && yValue >= minThreshold && yValue <= maxThreshold) {
    joyMovedY = false;
  }
}


void mainMenu()
{
  //function that prints the options of the main menu
  lcd.setCursor(1 , 0);
  lcd.print("Start");
  lcd.setCursor(7 , 0);
  lcd.print("HighScore");
  lcd.setCursor(1 , 1);
  lcd.print("Settings");
  lcd.setCursor(12 , 1);
  lcd.print("Info");
}



void levelMenu()
{
  //function that prints the options of the level menu
  lcd.setCursor(0 , 0);
  lcd.print(username);
  lcd.setCursor(9 , 0);
  lcd.print("Lives:");
  
  lcd.print(noOfLives);
  lcd.setCursor(3 , 1);
  lcd.print("Score:");
  lcd.print(score);
}

void finishedGameMenuNewHS()
{
  //function that prints the options of the finished game menu
  lcd.setCursor(1, 0);
  lcd.print("New highscore!");
  lcd.setCursor(0 , 1);
  lcd.print(maxScore);
  lcd.setCursor(11 , 1);
  lcd.print(">Exit");
}

void finishedGameMenuNoHS()
{
  //function that prints the options of the finished game menu
  lcd.setCursor(0 , 0);
  lcd.print("Game Over!Score is");
  lcd.setCursor(0 , 1);
  lcd.print(score);
  lcd.setCursor(7 , 1);
  lcd.print(" >Exit");
}

void finishedGameMenu()
{
  //display the message "new highscore", "game over", smiley face or sad face
  if(score == maxScore)finishedGameMenuNewHS();
  else finishedGameMenuNoHS();
  buttonState = digitalRead(buttonPin);
  if (buttonState !=  lastButtonState) {
  if (buttonState == LOW) {//button was pressed to exit this menu
     if(currentCursorPosition == 0 && modifyStartScreen == 2) //we are in the start menu, 2nd option(game finished)
     {
      modifyStartScreen = 4;
      score = 0;
      lcd.clear();
      lcd.print(">");
     } 
  }
  lastButtonState = buttonState;
  }
  

  
} 

void highScoreMenu()
{
  //display the highscore menu 
  lcd.setCursor(0 , 0);
  lcd.print("Highscore:");
  lcd.print(maxScore);
  lcd.setCursor(0 , 1);
  lcd.print(maxUsername);
  lcd.setCursor(11 , 1);
  lcd.print(">Exit");
 //exit when the button was pressed
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
const int noOfSetPos = 2;
Position setPos[noOfSetPos] = {
  {0 , 0} , {0 , 1}
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
    lcd.print("Exit");

    if(buttonPressedSettings == 1) //the name is editing
    {
      lcd.setCursor(currentStringPos + 6 , 0);
      lcd.print(" ");
      
      
    }
     
}
void printDifficulty()
{
  //prints the difficulty options before beginning the game
  lcd.setCursor(1 , 0);
  lcd.print("Easy");
  lcd.setCursor(9 , 0);
  lcd.print("Medium");
  lcd.setCursor(6 , 1);
  lcd.print("Hard");
}

void chooseDifficultyScreen()
{
  //set the cursor before your option 
  printDifficulty();
  if(buttonPressedDifficulty == 0)
  {
    yValue = analogRead(yPin);
    if (modifyStartScreen == 3 && yValue >= minThreshold && yValue <= maxThreshold) {
      joyMovedY = false;
    }

    if(modifyStartScreen == 3 && yValue < minThreshold && joyMovedY == false){
      if(cursorDifficultyPosition < 2)cursorDifficultyPosition ++;
      else cursorDifficultyPosition = 0;
      joyMovedY = true;
    }
    if(modifyStartScreen == 3 && yValue > maxThreshold && joyMovedY == false){
      if(cursorDifficultyPosition > 0) cursorDifficultyPosition --;
      else cursorDifficultyPosition = 2;
      joyMovedY = true;
    }
    if(joyMovedY == true){
      lcd.clear();
      printDifficulty();
      lcd.setCursor(difficultyPosition[cursorDifficultyPosition].col , difficultyPosition[cursorDifficultyPosition].row);
      lcd.print(">");
    } 
   }
   //check if the button was pressed(we have selected an option)
   buttonState = digitalRead(buttonPin);
    if (buttonState !=  lastButtonState) {
    if (buttonState == LOW) {//button was pressed
      if(modifyStartScreen == 3 && !buttonPressedDifficulty && currentCursorPosition == 0)
      {
         buttonPressedDifficulty = 1;
         timeWhenGameStarted = millis();
        switch(cursorDifficultyPosition)
        {
          case 0:speedPlayer = speedEasy;
                 valueMultiplyScore = valueMultiplyScoreEasy;
                 widthOfPath = 4;
                 restaurateWalls(patternWallsEasy); //this will happen only one time before starting the game. the other restauration will take place when we loose the game
                break;
          case 1:speedPlayer = speedMedium;
                 valueMultiplyScore = valueMultiplyScoreMedium;
                 widthOfPath = 3;
                 restaurateWalls(patternWallsMedium);
                break;
          case 2: speedPlayer = speedHard;
                  valueMultiplyScore = valueMultiplyScoreHard;
                  widthOfPath = 3;
                  restaurateWalls(patternWallsHard);
                break;
        }
      }
      else if(modifyStartScreen == 3 && buttonPressedDifficulty && currentCursorPosition == 0)
      {
        buttonPressedDifficulty = 0;
      }
    }
    lastButtonState = buttonState;
    }
}



void printTryAgain()
{
  lcd.setCursor(1 , 0);
  lcd.print("Try again?  (:");
  lcd.setCursor(1 , 1);
  lcd.print("Exit?       ):");
}


void tryAgainMenu()
{
  printTryAgain();
  if(buttonPressedTryAgain == 0)
  {
    xValueMenu = analogRead(xPin);
    if (modifyStartScreen == 4 && xValueMenu >= minThreshold && xValueMenu <= maxThreshold) {
      joyMovedXMenu = false;
    }

    if (modifyStartScreen == 4 && xValueMenu < minThreshold && joyMovedXMenu == false) { //we want to move between name level and exit
      joyMovedXMenu = true;
      cursorTryAgainPosition = !cursorTryAgainPosition;
      lcd.clear();
      printTryAgain();
      lcd.setCursor(tryAgainPosition[cursorTryAgainPosition].col , tryAgainPosition[cursorTryAgainPosition].row);
      lcd.print(">");
    }

    if(modifyStartScreen == 4 && xValueMenu > maxThreshold && joyMovedXMenu == false){
      joyMovedXMenu = true;
      cursorTryAgainPosition = !cursorTryAgainPosition;
      lcd.clear();
      printTryAgain();
      lcd.setCursor(tryAgainPosition[cursorTryAgainPosition].col , tryAgainPosition[cursorTryAgainPosition].row);
      lcd.print(">");
      
    }
  }
  
  buttonState = digitalRead(buttonPin);
    if (buttonState !=  lastButtonState) {
    if (buttonState == LOW) {//button was pressed
      if(modifyStartScreen == 4 && buttonPressedTryAgain == 0 && currentCursorPosition == 0)//we are in Start, the second menu after finishing the game and the button was not pressed
      {
        buttonPressedTryAgain = 1;
        switch(cursorTryAgainPosition)
        {
          case 0: modifyStartScreen = 3;//try again. restart the game
                  pressedStart = 1;
                  lcd.clear();
                  break;
          case 1: modifyStartScreen = 0; //exit. go in the main menu
                  mainMenuScreen = 1;
                  lcd.clear();
                  lcd.print(">");
                  mainMenu();
                  break;

        }
      }

    }
    lastButtonState = buttonState;
  }
}
void settingsMenu()
{
  //function that controlls the selected option of settings menu
  printSettingsMenu();

  if(buttonPressedSettings == 0)
  {
    xValueMenu = analogRead(xPin);
    if (modifySettingsScreen == 1 && xValueMenu >= minThreshold && xValueMenu <= maxThreshold) {
      joyMovedXMenu = false;
    }

    if (modifySettingsScreen == 1 && xValueMenu < minThreshold && joyMovedXMenu == false) { //we want to move between name level and exit
      
      currentSetPos = !currentSetPos;
      joyMovedXMenu = true;
      Serial.println(currentSetPos);
      lcd.clear();
      printSettingsMenu();
      lcd.setCursor(setPos[currentSetPos].col , setPos[currentSetPos].row);
      lcd.print(">");
    }

    if(modifySettingsScreen == 1 && xValueMenu > maxThreshold && joyMovedXMenu == false){
       
      currentSetPos = !currentSetPos;
      joyMovedXMenu = true;
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
          case 1: buttonPressedSettings = 2;//we want to exit
                  break;
        }
      }
      else if(modifySettingsScreen == 1 && currentCursorPosition == 2 && buttonPressedSettings != 0)
        buttonPressedSettings = 0;
        currentStringPos = 0;
  
    }
    lastButtonState = buttonState;
  }
  
  if(buttonPressedSettings == 2)
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
  if(buttonPressedSettings == 1)
  {
      setupName();
  }
  
}
String infoElements[] = {
  "Racing Game" , "Laura Cozma" , "github.com/Laur" , "aElenaCozma  " , "@UnibucRobotics" , "Exit" , "     "
};
int numberOfInfoElements = 7;
int positionInfoElements = 0;
bool buttonPressedInfo = 0; //is pressed is we want to go back

void infoMenu()
{
  //check if the button was pressed and we are on exit
  buttonState = digitalRead(buttonPin);
  if (buttonState !=  lastButtonState) {
    if (buttonState == LOW) {//button was pressed
      if(positionInfoElements == numberOfInfoElements - 2)buttonPressedInfo = true; //we go back only if > is on exit
    }
    lastButtonState = buttonState;
  }
  if(!buttonPressedInfo)
  {
    lcd.setCursor(0 , 0);
    lcd.print(">");
    lcd.setCursor(1 , 0);
    lcd.print(infoElements[positionInfoElements]);
    lcd.setCursor(1 , 1);
    lcd.print(infoElements[positionInfoElements + 1]);
  
    xValueMenu = analogRead(xPin);
    if (modifyInfoScreen == 1 && xValueMenu >= minThreshold && xValueMenu <= maxThreshold) {
        joyMovedXMenu = false;
    }
  
    if (modifyInfoScreen == 1 && xValueMenu < minThreshold && joyMovedXMenu == false && positionInfoElements > 0) { 
      positionInfoElements --;
      lcd.clear();
      joyMovedXMenu = true;
    }
  
    if(modifyInfoScreen == 1 && xValueMenu > maxThreshold && joyMovedXMenu == false && positionInfoElements < numberOfInfoElements - 2){ //we can't go down when we are on exit; positionInfoElements <= 3 so the last position is 4(after incrementing)
         
      positionInfoElements ++;
      joyMovedXMenu = true;
      lcd.clear();
    }
  }
  else
  {
     buttonPressedInfo = 0;
     positionInfoElements = 0;
     modifyInfoScreen = 0;
     mainMenuScreen = 1;
     lcd.clear();
     lcd.print(">");
     mainMenu();
  }
}


void buttonPressedMenu()
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
    xValueMenu = analogRead(xPin);
    if (mainMenuScreen == 1 && xValueMenu >= minThreshold && xValueMenu <= maxThreshold) {
      joyMovedXMenu = false;
    }
    if (mainMenuScreen == 1 && ((xValueMenu < minThreshold && joyMovedXMenu == false) || (xValueMenu > maxThreshold && joyMovedXMenu == false) || pressedButton == true)) { //we want to change the category
      lastButtonState = LOW;
      pressedButton = false;
      if(currentCursorPosition == 0) 
      {
        modifyStartScreen = 3;
        lcd.clear(); 
        mainMenuScreen = 0;
        pressedStart = 1; //we have started the game
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
      if(currentCursorPosition == 3)
      {
        lcd.clear();
        mainMenuScreen = 0;
        modifyInfoScreen = 1;
      }
    joyMovedXMenu = true;

  }

  }
  
  
}


void screenTransition()
{
  //function that calls the functions of the current type of menu
  if(modifyStartScreen == 1){
        if(pressedStart && !gameOver){
            levelMenu();
            if(!display321)
            {
              display321BeforeStart();
            }
            
        }
        if(pressedStart && gameOver)
        {
          switch(cursorDifficultyPosition)
          {
            case 0:speedPlayer = speedEasy;
                   valueMultiplyScore = valueMultiplyScoreEasy;
                   widthOfPath = 4;
                   restaurateWalls(patternWallsEasy); //this will happen only one time before starting the game. the other restauration will take place when we loose the game
                  break;
            case 1:speedPlayer = speedMedium;
                   valueMultiplyScore = valueMultiplyScoreMedium;
                   widthOfPath = 3;
                   restaurateWalls(patternWallsMedium);
                  break;
            case 2: speedPlayer = speedHard;
                    valueMultiplyScore = valueMultiplyScoreHard;
                    widthOfPath = 3;
                    restaurateWalls(patternWallsHard);
                  break;
          }
          secondLevel = false;
          thirdLevel = false;
          cursorDifficultyPosition = 0;
          timeWhenGameStarted = 0;
          restaurateWalls(patternWallsEasy);
          indexStartPath = 2;
          rowPlayer = 5;
          display321 = 0;
          gameOver = 0;
          noOfLives = 3;
          firstLifeGenerated = false;
          secondLifeGenerated = false;
          thirdLifeGenerated = false;
          increment1 = false;
          increment2 = false;
          increment3 = false;
          pressedStart = 0;
          currentColIntroInGame = 0;
          modifyStartScreen = 2;
          startingLevelValue = 0;
          if(score > maxScore) {
            displayMatrix(happyFace);
            digitalWrite(redLedPin , LOW);
            maxScore = score;
            maxUsername = username;
            char buf[noOfUsernamePos + 1];
            maxUsername.toCharArray(buf , noOfUsernamePos + 1);
            EEPROM.put(eeAdress , maxScore);
            EEPROM.put(eeAdress + sizeof(int), buf);
          }
          else {
            digitalWrite(greenLedPin , LOW);
            displayMatrix(sadFace);
          }
          
          lcd.clear();
           
        }
  }

  if(modifyStartScreen == 2){
    
        finishedGameMenu();
        firstInDifficulty = 1; //now we can go again for the first time in difficulty menu
        buttonPressedDifficulty = 0;

  }
  if(modifyStartScreen == 3){
        if(firstInDifficulty == 1) //to print only the first time the > in front of easy
        {
          lcd.setCursor(0 , 0);
          lcd.print(">");
          firstInDifficulty = 0;
        }
        if(!buttonPressedDifficulty)chooseDifficultyScreen();
        else {
          timeWhenGameStarted = millis();
          modifyStartScreen = 1;
          lcd.clear();
        }
  }
  if(modifyStartScreen == 4){
    Serial.println(buttonPressedTryAgain);

    if(!buttonPressedTryAgain)tryAgainMenu();
    else
    {
        buttonPressedTryAgain = 0;
        cursorTryAgainPosition = 0;
    }
    
  }
  if(modifyHighScoreScreen == 1){
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
  if(modifyInfoScreen == 1)
  {
    infoMenu();
  }
  
}


void displayIntroGame(){
  for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 8 ; col++)
        lc.setLed(0 , 7 - col , row , introInGameMatrix[row][(col + currentColIntroInGame) % noOfColumnsIntroInGame]);


  if(millis() - lastTime >= intervalScrollingIntro)
  {
    currentColIntroInGame++;
    lastTime = millis();
  } 

}


void restaurateWalls(bool w[][8])
{
  for(int row = 0 ; row < 8 ; row ++) 
    for(int col = 0 ; col < 8 ; col++)
    {
       bool val = pgm_read_byte_near(w[row] + col);
       walls[row][col] = val;
    }
      
}

void generateWalls(int width) //width of the path
{
  for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 7 ; col++)
      walls[row][col] = walls[row][col + 1];

  if(indexStartPath > randNumber) //move to the left
    {
        if(indexStartPath != 0) { //we can go to the left 
          walls[indexStartPath - 1][7] = 0; //if we had 1 0 0 0 1 1 1 1 now we have 0 0 0 1 1 1 1 1
          if(indexStartPath + width - 1 <= 7)walls[indexStartPath + width - 1][7] = 1;
          indexStartPath --;
        }
        
    }
   else if(indexStartPath < randNumber) //move to the right
   {  
      if(indexStartPath != 7){
        walls[indexStartPath][7] = 1;     //if indexStartPath == 7 we block the road
      }
      if(indexStartPath + width <= 7) walls[indexStartPath + width][7] = 0;
      if(indexStartPath != 7)
          indexStartPath ++;
      
   }
  
  if(indexStartPath == randNumber)
     randNumber = random(0 , 8); //we don't know the direction so we generate another one
}

void movePlayer()
{
  yValuePlayer = analogRead(pinY);

  if (yValuePlayer >= minThreshold && yValuePlayer <= maxThreshold) {
    joyMovedYPlayer = false;
  }

  if (yValuePlayer > maxThreshold && joyMovedYPlayer == false) {
     if(rowPlayer < 7)rowPlayer ++;
     joyMovedYPlayer = true;
  }
// Serial.println(rowPlayer);
  if (yValuePlayer < minThreshold && joyMovedYPlayer == false) {
       if(rowPlayer > 0)rowPlayer --;
      joyMovedYPlayer = true;
  }

}

int validMove()
{
  //check if the move is valid 
  if(walls[rowPlayer][colPlayer] == 1)
    {
      return 0;
    }
  else return 1;
}

void buttonPressed()
{
  swState = digitalRead(pinSW);

  if (swState !=  lastSwState) {
  if (swState == LOW) {
      pressedStart = !pressedStart;

      currentColIntroInGame = 0;
      currentColWalls = 0;
  }
  }
  lastSwState = swState;
}


void blinkPlayer()
{
  if(millis() - lastTimeBlinkPlayer >= (speedPlayer  / 4))
  {
    lastTimeBlinkPlayer = millis();
    stateBlinkPlayer = !stateBlinkPlayer;
  }
}

void drawMap()
{
  //draw the walls 
   for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 8 ; col++)
       lc.setLed(0 , row , col , walls[row][col]);

  if(!secondLevel && millis()- timeWhenGameStarted >= 10000)
     { speedPlayer -= 100;
       secondLevel = true;
     }
  if(!thirdLevel && millis()- timeWhenGameStarted >= 20000)
     { speedPlayer -= 100;
       thirdLevel = true;
     }
  if(millis() - lastTimeScrollWalls >= speedPlayer)
  {
    generateWalls(widthOfPath);
    lastTimeScrollWalls = millis();
    score += valueMultiplyScore;
    
    if(!validMove()){
      noOfLives --;
      if(noOfLives == 0) {gameOver = 1;}
      else{
      unsigned long long timeFreeze = millis();
      lcd.clear();
      levelMenu(); //we have lost a life and we want to be edesplayed on the screen
      noTone(buzzPin);
      while(millis() - timeFreeze <= 4000)
      {
         for(int row = 0 ; row < 8 ; row++)
          for(int col = 0 ; col < 8 ; col++)
              lc.setLed(0 , row , col , walls[row][col]);

        yValuePlayer = analogRead(yPin);
        if (modifyStartScreen == 1 && yValuePlayer >= minThreshold && yValuePlayer <= maxThreshold) {
          joyMovedYPlayer = false;
        }
    
        if(modifyStartScreen == 1 && yValuePlayer < minThreshold && joyMovedYPlayer == false){
          if(rowPlayer > 0) rowPlayer --;
          joyMovedYPlayer = true;
        }
        if(modifyStartScreen == 1 && yValuePlayer > maxThreshold && joyMovedYPlayer == false){
          if(rowPlayer < 7) rowPlayer ++;
          joyMovedYPlayer = true;
        }
        blinkPlayer();
        lc.setLed(0 , rowPlayer , colPlayer , stateBlinkPlayer);
      }
      }
    }
    
    }
 

}



 void generateLife()
{
  //start the buzzer for 3 seconds 
  if(millis()- timeWhenGameStarted > 10000 && timeWhenGameStarted != 0) //15 seconds after the game started
  {
    int randomNum = random(0 , 1000);
    if(freezeNoTone == false && randomNum >= 0 && randomNum <=50 && (millis() - lastTimeExtraLifeGenerated) > 5000 && firstLifeGenerated == false)
    {
      tone(buzzPin , 30000);
      lastTimeExtraLifeGenerated = millis();
      firstLifeGenerated = true;
    }
  }

  if(millis()- timeWhenGameStarted > 35000 && timeWhenGameStarted != 0) //after  seconds
  {
    int randomNum = random(0 , 1000);
    if(freezeNoTone == false && randomNum >= 0 && randomNum <=50 && (millis() - lastTimeExtraLifeGenerated) > 5000 && secondLifeGenerated == false)
    {
      tone(buzzPin , 35000);
      lastTimeExtraLifeGenerated = millis();
      secondLifeGenerated = true;
    }
  }
  if(millis()- timeWhenGameStarted > 100000 && timeWhenGameStarted != 0) //after  seconds
  {
    int randomNum = random(0 , 1000);
    
    Serial.println(randomNum);
    if(freezeNoTone == false && randomNum >= 0 && randomNum <=50 && (millis() - lastTimeExtraLifeGenerated) > 5000 && thirdLifeGenerated == false)
    {
      tone(buzzPin , 40000);
      lastTimeExtraLifeGenerated = millis();
      thirdLifeGenerated = true;
    }
  }
}


void stopBuzzer()
{
  //stop the buzzer after 3 seconds or by pressing the button
  if(firstLifeGenerated == true && secondLifeGenerated == false && millis() - lastTimeExtraLifeGenerated <=3000)
  {
    //first tone
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && !increment1 && modifyStartScreen == 1) {//button was pressed
      increment1 = true;
      noOfLives ++;
      noTone(buzzPin);
    }
   }

  if(firstLifeGenerated == true && secondLifeGenerated == true && thirdLifeGenerated == false && millis() - lastTimeExtraLifeGenerated <=3000)
  {
    //second tone
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && !increment2 && modifyStartScreen == 1) {//button was pressed
      increment2 = true;
      noOfLives ++;
      noTone(buzzPin);
    }
  }

  if(firstLifeGenerated == true && secondLifeGenerated == true && thirdLifeGenerated == true && millis() - lastTimeExtraLifeGenerated <=3000)
  {
    //third tone
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && !increment3 && modifyStartScreen == 1) {//button was pressed
      increment3 = true;
      noOfLives ++;
      noTone(buzzPin);
    }
  }

  if(millis() - lastTimeExtraLifeGenerated > 3000)
  { //haven't pressed the button, the tone must stop
    noTone(buzzPin);
    lastTimeExtraLifeGenerated = 0;
  }
}


void welcomeMessageMatrix()
{
  //print the welcome message when the board is connected
  for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 8 ; col++)
    {
      bool value = pgm_read_byte_near(welcomeMatrix[row] +  ((col + currentColWelcome) % 43));
      lc.setLed(0 , 7 - col , row , value);
    }


  if(millis() - lastTimeWelcome >= 230)
  {
    currentColWelcome++;
    lastTimeWelcome = millis();
  } 
  if(millis() > 10000) { 
    printedWelcome = 1; 
    lcd.clear();
    lcd.print(">");
     mainMenu();}
}

void welcomeMessageLCD(){
  lcd.setCursor(3 , 0);
  lcd.print("Racing Game");
  lcd.setCursor(4 , 1);
  lcd.print("Have fun!");
  
}

void setup() {
  pinMode(redLedPin , OUTPUT);
  pinMode(greenLedPin , OUTPUT);
  //int high = 0;
  //EEPROM.put(eeAdress , high);
  //EEPROM.put(eeAdress + sizeof(int) , "PLAYER ");
  // put your setup code here, to run once:
  lc.shutdown(0 , false);//we have one driver, the driver no. 0
  lc.setIntensity(0 , 2);//intensity between 0 and 15
  lc.clearDisplay(0);
  pinMode(pinSW , INPUT_PULLUP);
  for (int i = 0; i < 8; i++)
  {
    pinMode(rowComp[i], OUTPUT);
    pinMode(colComp[i], OUTPUT);
  } 
  
  Serial.begin(9600);

  pinMode(buttonPin , INPUT_PULLUP);
  lcd.begin(16 , 2); //number of columns and 2 rows
  EEPROM.get(eeAdress , maxScore);
  char buf[noOfUsernamePos + 1];
  EEPROM.get(eeAdress + sizeof(int) , buf);
  int cpos = 0;
  while(cpos < noOfUsernamePos)
  {
    maxUsername += buf[cpos];
    cpos ++;
  }
  Serial.println(buf);
  
  
}

void loop() { 
 
if(modifyStartScreen != 2)
{
  //the leds are turned on during the entire game, except the moment when the game is finished 
  digitalWrite(redLedPin , HIGH);
  digitalWrite(greenLedPin , HIGH);
}

if(millis() - lastTimeExtraLifeGenerated > 3000 || gameOver)
  {  
    //we died while the buzzer was singing, the tone stops
    noTone(buzzPin);
    lastTimeExtraLifeGenerated = 0;
  }
  
  if(!printedWelcome){
  welcomeMessageLCD();
  welcomeMessageMatrix();
  }
  else 
  {
    selectOptionMainMenu();
    buttonPressedMenu();
    screenTransition();
  }
  if(printedWelcome && pressedStart && !gameOver && display321)
  {
    generateLife();
    stopBuzzer();
    drawMap(); 
    movePlayer();
    blinkPlayer();
    lc.setLed(0 , rowPlayer , colPlayer , stateBlinkPlayer);

  }
  else if(printedWelcome && modifyStartScreen != 2) displayIntroGame();
 
}
