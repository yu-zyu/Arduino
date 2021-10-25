
int LED = 13;
String sendstr = "arduino";

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
    // シリアル通信機能の設定
  Serial.begin(4800, SERIAL_8O1, 26, 32);
 // Serial.println("Start writeing.");
}

void loop() {
  digitalWrite(LED, LOW);
      Serial.write("a");
  for (int i = 0; i < sendstr.length(); i++) {

  }
  // Serial.write(0);
  digitalWrite(LED, HIGH);
  delay(2000);
}
