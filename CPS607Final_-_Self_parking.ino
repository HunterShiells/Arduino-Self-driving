#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#include <Servo.h> 
Servo myservo;

int Echo = A4;  
int Trig = A5;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
int cspeed = 90;
int middleDistance = 0;
boolean hasseen = false, passed = false;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(3,700,2400);
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(180);
  forward();
  middleDistance = Distance_test();
  if(middleDistance<20){
    hasseen = true;
  }
  else if(middleDistance>30){
    hasseen = false;
    passed = true; 
  }
  if(hasseen==true and passed==true){
    stop();
    right();
    delay(300);
    stop();
    backward();
    delay(800);
    stop();
    left();
    delay(300);
    stop();
    backward();
    delay(200);
    stop();
    exit(0);
  }
}


void forward(){
  analogWrite(ENA, cspeed);
  analogWrite(ENB, cspeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void backward(){
  analogWrite(ENA, cspeed);
  analogWrite(ENB, cspeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void left(){
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void right(){
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
}

int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  
