// Connect to Arduino micro（本体ではMicroに接続していたため）

const int LED_PIN = 5;
const int SENSOR1 = A5;
const int SENSOR2 = A4;
int sensorValue[2] = {0, 0};
int serialValue = 0;
float serialValue_float = 0.0;

// 0 - 1023ゲージの内、最小閾値を設定
const int threshold_value = 30; 

void setup(){
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}


void loop(){
  sensorValue[0] = analogRead(SENSOR1);
  sensorValue[1] = analogRead(SENSOR2);
  delay(1); // 動作安定化

  // LED の動作
  if (sensorValue[0] > threshold_value || sensorValue[1] > threshold_value){
    digitalWrite(LED_PIN, HIGH);
  }else{
    digitalWrite(LED_PIN, LOW);
  }

  // 2つのセンサーの値を比較して、大きい値を選択
  if (sensorValue[0] < sensorValue[1]){
    sensorValue[0] = sensorValue[1];
  }

  // 最小閾値以下なら１を、そうでないなら、1/4した値を送信（byte型のbit数に依存）
  serialValue = sensorValue[0] - threshold_value + 1;
  if (serialValue < 1){
    Serial.write(1);
//    Serial.println(1);
  }else{
    serialValue = serialValue / 4;
    Serial.write(serialValue);
//    Serial.println(serialValue);
  }
  
  Serial.flush();
}
