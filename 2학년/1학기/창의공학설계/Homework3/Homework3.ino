//과제 3
//주제 : 초음파 레이더를 활용한 자율 주행 모드로 미로 탈출하기
//
//내용 : 대면 수업에서 언급한 초음파 레이더를 활용하여 자율 주행으로 미로를 탈출하는 미션을 수행합니다!
//      설치된 미로를 대상으로 출발선에서 출발하여 벽에 부딪히지 않고 출구로 나오면 미션 성공!

#include <Servo.h>
Servo myservo;

int RightMotor_E_pin = 5;      // 오른쪽 모터의 Enable & PWM
int LeftMotor_E_pin = 6;       // 왼쪽 모터의 Enable & PWM
int RightMotor_1_pin = 8;      // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 9;      // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 10;      // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 11;      // 왼쪽 모터 제어선 IN4

int trigPin = 13;
int echoPin = 12;

int L_MotorSpeed = 90; 
int R_MotorSpeed = 90; 

int distance_left = 0;
int distance_right = 0;

void sensor();

void setup() {
   myservo.attach(2);
   myservo.write(90);
   
  Serial.begin(9600);    // PC와의 시리얼 통신 9600bps로 설정
  pinMode(echoPin, INPUT);   // echoPin 입력
  pinMode(trigPin, OUTPUT); 
  
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  
  Serial.println("ready..");
}

void loop() {
  sensor();
}

void sensor(){
  long duration, distance;
  digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 1000) / 2;
  Serial.println(distance);
  
  if(distance > 60)
  {
    Serial.println("Forward");
    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, HIGH);
    digitalWrite(LeftMotor_4_pin, LOW);
    analogWrite(RightMotor_E_pin, R_MotorSpeed);
    analogWrite(LeftMotor_E_pin, L_MotorSpeed);
  }
  else
  {
    Serial.println("Stop");
    digitalWrite(RightMotor_1_pin, LOW);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, LOW);

    myservo.write(180);
    delay(2000);
    digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance_left = ((float)(340 * duration) / 1000) / 2;
    
    myservo.write(0);
    delay(2000);
    digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance_right = ((float)(340 * duration) / 1000) / 2;

    myservo.write(90);

    Serial.println(distance_right);
    Serial.println(distance_left);

    if(distance_right>distance_left){
      Serial.println("turn_right");
      digitalWrite(RightMotor_1_pin, LOW);
      digitalWrite(RightMotor_2_pin, HIGH);
      digitalWrite(LeftMotor_3_pin, HIGH);
      digitalWrite(LeftMotor_4_pin, LOW);
      analogWrite(RightMotor_E_pin, 130);
      analogWrite(LeftMotor_E_pin, 130);
      delay(1380);
    }
    else {
      Serial.println("turn_left");
      digitalWrite(RightMotor_1_pin, HIGH);
      digitalWrite(RightMotor_2_pin, LOW);
      digitalWrite(LeftMotor_3_pin, LOW);
      digitalWrite(LeftMotor_4_pin, HIGH);
      analogWrite(RightMotor_E_pin, 130);
      analogWrite(LeftMotor_E_pin, 130);
      delay(1380);
    }
  }
}
