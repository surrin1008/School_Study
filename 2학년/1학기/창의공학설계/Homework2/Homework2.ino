//과제 2
//주제 : 라인트레이서 센서를 활용한 검은색 라인 트랙 자율 주행하기
//
//내용 : 팀별로 제공된 검은색 라인 경기장에서 출발선에서 출발하고 도착선에서 멈추는 미션 수행
//      라인을 벗어나면 실격처리됨

int RightMotor_E_pin = 5;      // 오른쪽 모터의 Enable & PWM
int LeftMotor_E_pin = 6;       // 왼쪽 모터의 Enable & PWM
int RightMotor_1_pin = 8;      // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 9;      // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 10;      // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 11;      // 왼쪽 모터 제어선 IN4

int R_Line = A3; 
int C_Line = A4; 
int L_Line = A5; 

int L_MotorSpeed = 100; 
int R_MotorSpeed = 100; 

int SR = 1;
int SC = 1;
int SL = 1;

void setup() {
  pinMode(RightMotor_E_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);

  Serial.begin(9600);    // PC와의 시리얼 통신 9600bps로 설정
  Serial.println("Welcome Eduino!");
}

void loop() {
  int R = digitalRead(R_Line);
  int C = digitalRead(C_Line);
  int L = digitalRead(L_Line);
  
  Serial.print("digital : "); 
  Serial.print(L); 
  Serial.print(", "); 
  Serial.print(C); 
  Serial.print(", "); 
  Serial.print(R); 
  Serial.print("   ");

  if ( L == LOW && C == LOW && R == LOW ) {           // 0 0 0
    L = SL; C = SC; R = SR;
  }

  if ( L == LOW && C == HIGH && R == LOW ) {          // 0 1 0
    motor_role(HIGH, HIGH);
    Serial.println("직진");
  }
  
  else if (L == LOW && R == HIGH ){                   // 0 0 1, 0 1 1
    motor_role(LOW, HIGH);
    Serial.println("우회전");
  }
 
  else if (L == HIGH && R == LOW ) {                  // 1 0 0, 1 1 0
    motor_role(HIGH, LOW);
    Serial.println("좌회전");

  }
  else if ( L == HIGH && R == HIGH ) {                // 1 1 1, 1 0 1
    analogWrite(RightMotor_E_pin, 0);
    analogWrite(LeftMotor_E_pin, 0);
    Serial.println("정지");
  }
  SR = R;
  SC = C; 
  SL = L; 
}

void motor_role(int R_motor, int L_motor) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, R_MotorSpeed);
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);
}
