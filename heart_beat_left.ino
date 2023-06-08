// 上からみてピストン左側のモーターの制御

#include <Stepper.h>

int AIN1 = 4;
int AIN2 = 5;
int BIN1 = 6;
int BIN2 = 7;
int STEP = 200;
int STARTBUTTON = 11;
bool flag = false;
int value = 0;
Stepper myStepper(STEP, AIN1, BIN1);
int rotate = 110;  // モーター回転角


void setup() {
//  Serial.begin(9600);　　// デバッグ・将来の左右共通運動用
  myStepper.setSpeed(40);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STARTBUTTON, INPUT);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
}


void loop() {
  if(flag){
    // 周期ピストン運動を行う
    myStepper.step(rotate);
    myStepper.step(-1 * rotate);
    delay(1000);
  }else{
    // ボダンを押すまで始動しない（回路は間違えているため、動かない場合LOWにすると動く）
    Serial.write(0);
    if(digitalRead(STARTBUTTON) == HIGH){
      flag = true;
    }
  }
}
