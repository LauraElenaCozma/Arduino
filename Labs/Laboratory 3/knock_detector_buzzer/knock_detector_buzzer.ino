const int passiveBuzzerPin = A0;
const int activeBuzzerPin = 11;
const int pushButton = 2;

int passiveBuzzerValue = 0;
int activeBuzzerTone = 700;
int buttonState = 0;
int threshold = 10;
int lastPassiveBuzzerValue = 0;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
const int timeInterval = 5000;

void setup() {
  // put your setup code here, to run once:
  pinMode(passiveBuzzerPin , INPUT);
  pinMode(activeBuzzerPin , OUTPUT);
  pinMode(pushButton , INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  
  passiveBuzzerValue = analogRead(passiveBuzzerPin); //read the value of the knock(if it exists)
  
  currentTime=millis(); //we measure the time
  
  if(passiveBuzzerValue >= threshold) {
    lastPassiveBuzzerValue = passiveBuzzerValue; //we have detected a knock and we keep the value of the knock and the time when it has produced
    lastTime = millis();
    Serial.println(passiveBuzzerValue);
    }
    
  if(currentTime - lastTime >= timeInterval) {//if 5 seconds passed
    
     if(lastPassiveBuzzerValue != 0){ //and if we detected a real knock -- with a value bigger than threshold 
      
        tone(activeBuzzerPin , activeBuzzerTone); //the active buzzer starts singing
        lastTime = currentTime;
     }
     
  }
  buttonState = digitalRead(pushButton);
  if(buttonState==0){ //we pressed the button so the buzzer should stop singing
    
    noTone(activeBuzzerPin);
    lastPassiveBuzzerValue = 0;
  } 
}
