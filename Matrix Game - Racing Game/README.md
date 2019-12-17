# RACING GAME

## **Description**

Racing Game is a single player game. The player, represented on the matrix as a blinking point, must avoid the red lights on the matrix. The red lights will look like two walls, and the player must slip through them. When the player hits the wall, he loses a life, the game stops for a short period of time, the number of lives remaining will be displayed on the matrix, then the game will start. When the player loses all 3 lives, he will lose the game and a message will be displayed on the matrix.

When the game starts, the player can choose the difficulty of the level: "Easy", "Normal" and "Hard". After choosing a level, the game starts and the LCD will show the current score and the number of lives. The player can also set an username and can see the highscore, which is saved using EEPROM.

During the game, the player will hear a song generated using the buzzer. At the end of the game a green Led will light if the player has exceeded the highscore, otherwise the red one. During the game, the song may stop for 5 seconds. If you press the joystick button in that interval, you get an extra life. The joystick will be used to move us through the menu, respectively its left-right moves for the game.

## **1. Hardware**
- Arduino uno
- 2 medium-sized breadboards
- 1 small breadboard
- 8x8 LED matrix
- MAX7219 Driver
- 1 electrolytic capacitor of 10μF
- 1 ceramic capacitor of 104pF
- LCD
- 1 potentiometer
- 1 buzzer
- a green LED
- a red LED
- Joystick
- 3 220 ohm resistors
- 1 10K ohm resistor
- wires

## **2. Game specifications**
 - Welcome
 After you turn on the Arduino Uno board, a "Welcome!" message will be displayed on the matrix and "Racing Game, Have fun!" on the LCD for 10 seconds.
 - Start Game
As long as the game has not started, the text "START GAME" will be written on the matrix.

 ***Main Menu ***
 
 The Main Menu contains the following options:
  1. Start
  2. HighScore
  3. Settings
  4. Info
  
  Now you can scroll through the menu (displayed on the LCD) with the joystick. In order to move between the options you move the joystick left-right (on the OY axis). ONLY in the Main Menu (here) you can select an option by pressing the button of the joystick or by moving it on the OX AXIS(up or down). 
  
  ***Start***
  
  After pressing "Start" option, the possible difficulties of the game will appear on the LCD: "Easy", "Medium", "Hard". You can scroll through them by moving the joystick on the OY axis (left-right) and select one by pressing the button of the joystick. After selecting an option, the game will start. 
 
 
  ***HighScore***
  
  It contains:
  1. the highest score ever obtained by a player (saved in EEPROM)
  2. the name of the player that obtained the highest score, which is set in settings (saved in EEPROM)
  3. exit
  You can go back in the Main Menu only by pressing the button of the joystick
  
  ***Settings***
  
  The Settings Menu contains:
  1. the name 
  2. exit
  You can select an option moving the joystick up and down (on the OX axis). PAY ATTENTION! To modify the name you should press the button when ">" is set before "Name". To go back int the Main Menu you should press the button  when ">" is set before "Exit".
  Setting the name:
  After you have selected name in order to modify it (by pressing the button) you can do the following:
  - move left - right to know which letter you want to modify (the selected one will be purple)
  - move up - down to change the letter. Between A and Z it is " "
   Name has a maximum of 7 letters and the default name is "PLAYER ".
  
  ***Info***
  
  It contains:
  1. the name of the game (Racing Game)
  2. the creator name (Cozma Laura)
  3. Github link of the creator
  4. @UnibucRobotics (that helped me to create the game)
  5. exit
  You can scroll up and down using the OX axis. You can go back in the Main Menu only if the cursor ">" is set before "Exit" and you push the button.
