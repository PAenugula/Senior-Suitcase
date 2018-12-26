const int trigPin = 7;
const int echoPin = 10;
const int buzzPin = 4;
const int gLed = 39;
const int yLed = 35;
const int rLed = 31;


void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzPin,OUTPUT);
  //tone(buzzPin,2000,5000);
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(gLed,OUTPUT);
  pinMode(yLed,OUTPUT);
  pinMode(rLed,OUTPUT);
  
}

void loop() {
  beeperControl();
  
}
void beeperControl(){
  long distance = readDistance();
  if(distance < 30){
    Serial1.println("0");
    digitalWrite(rLed,HIGH);
    digitalWrite(gLed,LOW);
    digitalWrite(yLed,LOW);
    delay(2000);
  }
  if(distance < 60 && distance > 30){
    tone(buzzPin,1000,100);
    digitalWrite(yLed,HIGH);
    digitalWrite(rLed,LOW);
    digitalWrite(gLed,LOW);
    delay(freqFunction(distance));
  }else{
    digitalWrite(gLed,HIGH);
    digitalWrite(yLed,LOW);
    digitalWrite(rLed,LOW);
  }

}

long readDistance(){
  long dur;
  long distance;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  dur = pulseIn(echoPin, HIGH);
  distance = (((dur/2)/29.1));
  
  return distance;
}
void testFunction(){
  if(Serial.available()){
    int x = Serial.parseInt();
    Serial.println(freqFunction(x));
  }
}

int freqFunction(int x){
  int y = 0;
  y = (x-61);
  y = y*500;
  y = y/30+500;
  return y;
}
