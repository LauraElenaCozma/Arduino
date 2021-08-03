int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("I received: "); 
    Serial.println(incomingByte ); //prints in ascii code
    
    Serial.print("I received (DEC): "); //in decimal format
    Serial.println(incomingByte , DEC); 

    Serial.print("I received (HEX): "); 
    Serial.println(incomingByte , HEX); 

    Serial.print("I received (OCT): "); 
    Serial.println(incomingByte , OCT); 

    Serial.print("I received (BIN): "); 
    Serial.println(incomingByte , BIN); 

    char ch = (char)incomingByte;
    Serial.print("I received : "); 
    Serial.println(ch); 
  }
}
