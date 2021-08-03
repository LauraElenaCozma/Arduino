const int buttonPin = 2;
const int ledPin = 13;

int ledState = HIGH;
int buttonState = 0;                //ce valoare avea butonul ultima oara cand s a schimbat starea ledului
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;  //a timer. during 50 ms checks if the button keeps its state
unsigned long debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin , INPUT_PULLUP);
  pinMode(ledPin , OUTPUT);
  digitalWrite(ledPin , ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(buttonPin);    //current state of the button
  if(reading != lastButtonState)
  {  
    lastDebounceTime = millis();
  }
  if((millis() - lastDebounceTime) > debounceDelay)
  {
    if(reading != buttonState)
    {
      buttonState = reading;
      if(buttonState == LOW)  //if the button is pressed, we change the state
      {
        ledState = !ledState;
      }
    }
  }

  digitalWrite(ledPin , ledState);
  lastButtonState = reading;
  
}
