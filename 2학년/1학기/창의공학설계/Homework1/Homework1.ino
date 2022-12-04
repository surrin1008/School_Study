//과제 1
//주제 : 초음파 센서 및 모터를 이용한 벽에 충돌하지 않고 돌아서 멈추는 과제
//
//내용 : 초음파 센서를 이용하여 연속하여 거리를 측정하다 약 10cm 이내로 줄어들면
//      제자리 돌기를 통해 턴한 후 일정 거리 직진 후 멈추면 됨
//      벽에 부딪치면 실격

int trigPin = 13;
int echoPin = 12;
int RightMotor_E_pin = 5;      // 오른쪽 모터의 Enable & PWM
int RightMotor_1_pin = 8;      // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 9;     // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 10;      // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 11;      // 왼쪽 모터 제어선 IN4
int LeftMotor_E_pin = 6;      // 왼쪽 모터의 Enable & PWM

int count = 0 ;

int L_MotorSpeed = 100; // 왼쪽 모터 속도
int R_MotorSpeed = 100; // 오른쪽 모터 속도

void Sensor();

void setup() {
  Serial.begin(9600);       // 시리얼 속도 설정
  pinMode(echoPin, INPUT);   // echoPin 입력
  pinMode(trigPin, OUTPUT);  // trigPin 출력
  pinMode(RightMotor_E_pin, OUTPUT);        // 출력모드로 설정
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
}

void loop() {

  Sensor();
  
  
}

void Sensor()
{
  long duration, distance;
  digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);                  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 10000) / 2; 
  Serial.print("distance:");                          // 물체와 초음파 센서간 거리를 표시
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  
  if(count == 1)
  {
   Serial.println("Stop");
    digitalWrite(RightMotor_1_pin, LOW);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, LOW);
    analogWrite(RightMotor_E_pin, L_MotorSpeed);
    analogWrite(LeftMotor_E_pin, R_MotorSpeed);
  }
  else if(distance >= 20)
  {
    Serial.println("Forward");
    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, HIGH);
    digitalWrite(LeftMotor_4_pin, LOW);
    analogWrite(RightMotor_E_pin, L_MotorSpeed);
    analogWrite(LeftMotor_E_pin, R_MotorSpeed);
  }
  else
  {
    L_MotorSpeed = 153; // 왼쪽 모터 속도
    R_MotorSpeed = 153; // 오른쪽 모터 속도

    Serial.println("U_turn");
    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, LOW);
    digitalWrite(LeftMotor_4_pin, HIGH);
    analogWrite(RightMotor_E_pin, L_MotorSpeed);
    analogWrite(LeftMotor_E_pin, R_MotorSpeed);
    delay(1300);
    Serial.println("Forward");
    digitalWrite(RightMotor_1_pin, HIGH);
    digitalWrite(RightMotor_2_pin, LOW);
    digitalWrite(LeftMotor_3_pin, HIGH);
    digitalWrite(LeftMotor_4_pin, LOW);
    analogWrite(RightMotor_E_pin, L_MotorSpeed);
    analogWrite(LeftMotor_E_pin, R_MotorSpeed);
    delay(1500);
    count = 1;
  }
}
