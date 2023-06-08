// control heart crunk

#include <Stepper.h>

// PIN NUMBER
int AIN1 = 4;
int AIN2 = 5;
int BIN1 = 6;
int BIN2 = 7;

// MOTOR SETTING
int STEP = 200;
Stepper myStepper(STEP, AIN1, BIN1);

// SERIAL COMMUNICATION
String str;
String value;
int data = 0;
int buf = 0;

// CONTROL MOTOR PROPERTY
int before_angle = 0;
int now_state = 0;
int angle[3];
int standby_angle = 15;
int weak_angle = 62;    
int strong_angle = 78; 

// 強弱閾値設定（heart_grabber と値をあわせる）
int weak_level = 70;
int strong_level = 160;

// SKIP WEAKMODE（弱モードを省略するときはこの変数に関係するコードのコメントアウトをはずす）
//int PINFLAG = 8;



// SETUP FUNCTION
void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(14);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
//  pinMode(PINFLAG, INPUT);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  angle[0] = standby_angle * STEP / 360;
  angle[1] = weak_angle * STEP / 360;
  angle[2] = strong_angle * STEP / 360;
}

// MAIN FUNCTION
void loop() {
  str = Serial.read();
  data = str.toInt();

//  if(data > 0 && digitalRead(PINFLAG) == LOW){  // If Serial connection is faliure or initialize(0)
  if(data > 0){  // If Serial connection is faliure or initialize(0)
    if(data > weak_level && now_state == 0){
      myStepper.step(angle[1] - angle[now_state]);
      now_state = 1;
      delay(100);
    }else if(data > strong_level && now_state == 1){
      myStepper.step(angle[2] - angle[now_state]);
      now_state = 2;
      delay(300);
    }else if(data < strong_level - 20 && now_state == 2){
      delay(300);
      myStepper.step(angle[1] - angle[now_state]);
      now_state = 1;
    }else if(data < weak_level - 20 && now_state == 1){
      delay(100);
      myStepper.step(angle[0] - angle[now_state]);
      now_state = 0;
    }
//  }else if(data > 0 && digitalRead(PINFLAG) == HIGH){
//    if(data > weak_level && now_state == 0){
//      myStepper.step(angle[2] - angle[now_state]);
//      now_state = 2;
//      delay(100);
//    }else if(data < weak_level - 20 && now_state == 2){
//      delay(100);
//      myStepper.step(angle[0] - angle[now_state]);
//      now_state = 0;
//    }
  }
  Serial.flush();
}
