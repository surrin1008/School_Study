//과제 4
//주제 : 적외선 리모컨을 이용한 미로 탈출 및 라인트레이스 연동 과제
//
//내용 : 적외선 리모컨을 이용하여 수동으로 제어하여 미로를 탈출하고,
//      모드를 라인트레이서 모드로 변경하여 자율 주행으로 검은색 라인을 통과하는 과제
//      이 때 미로 탈출은 주어진 미로에 대해 입구 위치에서 출발하여 출구로 나오는 미션 수행
//      중간에 벽에 부딪히면 실격처리

#include <IRremote.h>
int RECV_PIN = A0;              // 적외선 수신센서 핀(아날로그 입력 A0)
IRrecv irrecv(RECV_PIN);        // 적외선 송수신 통신을 위한 객체
decode_results IR_Signal;       // 적외선 수신값 해석을 위한 객체

int RightMotor_E_pin = 5;       // 오른쪽 모터의 Enable & PWM
int LeftMotor_E_pin = 6;        // 왼쪽 모터의 Enable & PWM
int RightMotor_1_pin = 8;       // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 9;       // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 10;       // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 11;       // 왼쪽 모터 제어선 IN4

int R_Line = A3; 
int C_Line = A4; 
int L_Line = A5; 

int SR = 0;
int SC = 1;
int SL = 0;


int L_MotorSpeed = 150; 
int R_MotorSpeed = 150; 
int motor_s = 153;              // 최대 속도(0~255)의 60% 

int R_Motor = 0;
int L_Motor = 0;
int mode = 0;

void setup() {
  pinMode(RightMotor_E_pin, OUTPUT);        // 출력모드로 설정
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);

  Serial.begin(9600);                       // PC와의 시리얼 통신 9600bps로 설정
  Serial.println("Welcome Eduino!");
  
  irrecv.enableIRIn(); // 적외선 통신 수신 시작
}

void loop() { 
  if(irrecv.decode(&IR_Signal)){      // 적외선(IR) 수신값이 있는지 판단.       

    Serial.print("Input Signal : ");
    Serial.print("HEX[ "); Serial.print(IR_Signal.value, HEX); Serial.print(" ], ");
    Serial.print("Int[ "); Serial.print((String)IR_Signal.value); Serial.print(" ] || ");
    
    control_SmartCar((String)IR_Signal.value);

    if(mode == 0){
      motor_role(R_Motor, L_Motor, motor_s);
    }
    else if(mode == 1){
      Right_role();
    }
    else if(mode == 2){
      Left_role();
    }
    else if(mode == 4)
    {
      while(true)
      {      
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
          motor_roles(HIGH, HIGH);
          Serial.println("직진");
        }
        
        else if (L == LOW && R == HIGH ){                   // 0 0 1, 0 1 1
          motor_roles(LOW, HIGH);
          Serial.println("우회전");
        }
       
        else if (L == HIGH && R == LOW ) {                  // 1 0 0, 1 1 0
          motor_roles(HIGH, LOW);
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
    }
    else{
      motor_role(R_Motor, L_Motor, 0);
    }
    irrecv.resume();  // 다음 적외선 값 수신   
  } 
}

void control_SmartCar(String Remote_Val){ 
  if( Remote_Val == "16754775" ){      // "+" 버튼, 명령 : 속도 증가
    mode =4 ; 
  }
  
  else if(Remote_Val == "16718055" ){  // "2" 버튼, 명령 : 전진
    R_Motor = HIGH; L_Motor = HIGH; mode = 0;
    Serial.print("Forward : ");
  }  
  
  else if( Remote_Val == "16716015" ){ // "4" 버튼, 명령 : 좌회전
    mode = 2;
    Serial.print("Turn Left : "); 
  }
  
  else if( Remote_Val == "16734885" ){ // "6" 버튼, 명령 : 우회전
    mode = 1;
    Serial.print("Turn Right : "); 
  }
  
  else if( Remote_Val == "16730805" ){ // "8" 버튼, 명령 : 후진
    R_Motor = LOW; L_Motor = LOW; mode = 0;
    Serial.print("Backward : "); 
  }

  else if( Remote_Val == "16726215" ){ // "5" 버튼, 명령 : 정지
    mode = 3;
    Serial.print("Stop : ");  
  }
  
  else{
    Serial.print("Not Defined : ");  // 지정하지 않은 주소입력.
  }
  
  Serial.print("R_Motor[ ");Serial.print(R_Motor);Serial.print(" ], ");
  Serial.print("L_Motor[ ");Serial.print(L_Motor);Serial.print(" ], ");
  Serial.print("motor_s[ ");Serial.print(motor_s);Serial.print(" ], ");
  Serial.print("Mode[ ");Serial.print(mode);Serial.println(" ]");
}

void motor_role(int R_motor, int L_motor, int Speed){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, Speed);  // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, Speed);   // 좌측 모터 속도값  
}

void Right_role(){
   digitalWrite(RightMotor_1_pin, LOW);
   digitalWrite(RightMotor_2_pin, HIGH);
   digitalWrite(LeftMotor_3_pin,HIGH);
   digitalWrite(LeftMotor_4_pin, LOW);
   
   analogWrite(RightMotor_E_pin, 153);  // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, 153);   // 좌측 모터 속도값
}

void Left_role(){
   digitalWrite(RightMotor_1_pin, HIGH);
   digitalWrite(RightMotor_2_pin, LOW);
   digitalWrite(LeftMotor_3_pin, LOW);
   digitalWrite(LeftMotor_4_pin,HIGH);
   
   analogWrite(RightMotor_E_pin, 153);  // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, 153);   // 좌측 모터 속도값   
}
void motor_roles(int R_motor, int L_motor) {
  digitalWrite(RightMotor_1_pin, R_motor);
  digitalWrite(RightMotor_2_pin, !R_motor);
  digitalWrite(LeftMotor_3_pin, L_motor);
  digitalWrite(LeftMotor_4_pin, !L_motor);

  analogWrite(RightMotor_E_pin, R_MotorSpeed);
  analogWrite(LeftMotor_E_pin, L_MotorSpeed);
}
