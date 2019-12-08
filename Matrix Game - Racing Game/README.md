# RACING GAME

## **Description**

Racing Game is a single player game. The player, represented on the matrix as a blinking point, must avoid the red lights on the matrix. The red lights will look like two walls, and the player must slip through them. When the player hits the wall, he loses a life, the game stops for a short period of time, the number of lives remaining will be displayed on the matrix, then the game will start. When the player loses all 3 lives, he will lose the game and a message will be displayed on the matrix.

When the game starts, the player can choose the difficulty of the level: "Easy", "Normal" and "Hard". After choosing a level, the game starts and the LCD will show the current score and the number of lives. The player can also set an username and can see the highscore, which is saved using EEPROM.

During the game, the player will hear a song generated using the buzzer. At the end of the game a green Led will light if the player has exceeded the highscore, otherwise the red one. During the game, the song may stop for 5 seconds. If you press the joystick button in that interval, you get an extra life. The joystick will be used to move us through the menu, respectively its left-right moves for the game.

## **Necessary components**
- 8x8 LED matrix
- LCD
- Joystick
- MAX7219 Driver
- Wires
- 1 potentiometer
- 1 buzzer
- a green LED
- a red LED
- 1 medium-sized breadboard
- 1 small breadboard
- Arduino uno
