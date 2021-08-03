#include "LedControl.h"
LedControl lc = LedControl(12 , 11 , 10 , 1); //DIN , CLK , LOAD , No of drivers

void setup() {
  
  lc.shutdown(0 , false);//we have one driver, the driver no. 0
  lc.setIntensity(0 , 2);//intensity between 0 and 15
  lc.clearDisplay(0);
}

void loop() {
  for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 8 ; col++){
      lc.setLed(0 , col , row , true);//drive no, col, row, true - turns on the led 
      delay(25);
    }
    
  for(int row = 0 ; row < 8 ; row++)
    for(int col = 0 ; col < 8 ; col++){
      lc.setLed(0 , col , row , false);//drive no, col, row, true - turns on the led; turn off one by one
      delay(25);   
    }
  
}
