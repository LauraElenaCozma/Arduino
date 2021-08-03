const int trigPin = 9;
const int echoPin = 10;

long duration;
long distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin , LOW); //to clear 
  delayMicroseconds(2);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);//the sound is emitted for 10 micro sec
  digitalWrite(trigPin , LOW);//we turn it off
  duration = pulseIn(echoPin , HIGH);  //pulse in returns the time. pulseIn gives the time between trig being high and low
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
}
