//Hunter Shiells
//500946154

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
int middleDistance = 0, lane = 0;
boolean lt = true, passed = false, hasalready = false; 

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
  myservo.write(90);
  delay(2);
  forward();
  middleDistance = Distance_test();
  if(middleDistance <=5){
      stop();
      delay(400);
      middleDistance = Distance_test();
      if(middleDistance <= 8){ 
        if(lt and hasalready == false){
          stop();
          left();
          delay(175);
          stop();
          while(true){
          forward();
          if(LT_R or LT_L){
            passed = true;
            if(lane >= 12){
              stop();
              break;
            }
            delay(50);
          }
          if(passed == true){
            lane++;
            passed = false;
          }
          }
          lane = 0;
          lt = false;
          passed = false;
          hasalready = true;
          stop();
          right();
          delay(150);
          stop(); 
        }
        if(lt==false and hasalready == false){
          stop();
          right();
          delay(175);
          stop();
          while(true){
          forward();
          if(LT_R or LT_L){
            passed = true;
            if(lane >= 12){
              stop();
              break;
            }
            delay(50);
          }
          if(passed == true){
            lane++;
            passed = false;
          }
          }
          lane = 0;
          lt = true;
          passed = false;
          hasalready = true;
          stop();
          left();
          delay(125);
          stop();  
        }
        hasalready = false; 
      }
      else if (middleDistance > 8){
          while (true){
            stop();
            forward();
            if(LT_R){
              stop();
              backward();
              delay(100);
              stop();
              left();
              delay(100);
              stop();
              }
            if(LT_L){
              stop();
              backward();
              delay(100);
              stop();
              right();
              delay(100);
              stop();
              }
            delay(5);
            middleDistance = Distance_test();
            delay(5);
            if(middleDistance <=20){
              cspeed --;
              if(cspeed<=70){
                cspeed = 90; 
              }
            }
            if(middleDistance >=21){
              cspeed ++;
              if(cspeed >300){
                cspeed = 180;
              }
            }
            if(middleDistance  >=200){
              cspeed = 90;
              break;
            }
          }
        }
      }
  if(LT_R){
    stop();
    backward();
    delay(100);
    stop();
    left();
    delay(100);
    stop();
  }
  if(LT_L){
    stop();
    backward();
    delay(100);
    stop();
    right();
    delay(100);
    stop();
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

//Hunter Shiells
//500946154
