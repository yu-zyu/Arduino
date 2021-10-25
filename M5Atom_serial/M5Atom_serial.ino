
char buff[255];
int counter = 0;
int LED = 13;

void setup() {

  M5.begin();
  delay(10);
  //Serial.begin(115200);

  // シリアル通信機能の設定
  //Serial2.begin(9600);

    // シリアル通信機能の設定
  Serial2.begin(4800, SERIAL_8O1, 26, 32);

}

void loop() {
  M5.update();      // update button stateh
  
   char key;     // 受信データを格納するchar型の変数

  // 受信データがあった時だけ、処理を行う
  if ( Serial.available() ) {       // 受信データがあるか？
    key = Serial.read();            // 1文字だけ読み込む
    Serial.write( key );            // 1文字送信。受信データをそのまま送り返す。
  }

}
