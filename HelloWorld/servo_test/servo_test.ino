//tugai
#include <Servo.h>

Servo servo1; // サーボに名前を付ける
int volume1 = A1; // ボリューム抵抗をつなぐピン
int analog1; // ボリューム抵抗をアナログで読んだ値

Servo servo2; // サーボに名前を付ける
int volume2 = A2; // ボリューム抵抗をつなぐピン
int analog2; // ボリューム抵抗をアナログで読んだ値

Servo servo3; // サーボに名前を付ける
int volume3 = A3; // ボリューム抵抗をつなぐピン
int analog3; // ボリューム抵抗をアナログで読んだ値

Servo servo4; // サーボに名前を付ける
int volume4 = A4; // ボリューム抵抗をつなぐピン
int analog4; // ボリューム抵抗をアナログで読んだ値

void setup() {
servo1.attach(2); // サーボをつなぐピン
servo2.attach(3); // サーボをつなぐピン
servo3.attach(4); // サーボをつなぐピン
servo4.attach(5); // サーボをつなぐピン

}

void loop() {
analog1 = analogRead(volume1); // ボリューム抵抗を読む(0~1023)
analog1 = map(analog1, 0, 1023, 0, 180); // サーボの角度(0~180)
servo1.write(analog1); // 読んだ値によってサーボを動かす

analog2 = analogRead(volume2); // ボリューム抵抗を読む(0~1023)
analog2 = map(analog2, 0, 1023, 0, 180); // サーボの角度(0~180)
servo2.write(analog2); // 読んだ値によってサーボを動かす

analog3 = analogRead(volume3); // ボリューム抵抗を読む(0~1023)
analog3 = map(analog3, 0, 1023, 0, 180); // サーボの角度(0~180)
servo3.write(analog3); // 読んだ値によってサーボを動かす

analog4 = analogRead(volume4); // ボリューム抵抗を読む(0~1023)
analog4 = map(analog4, 1023, 0, 0, 180); // サーボの角度(0~180)
servo4.write(analog4); // 読んだ値によってサーボを動かす


delay(15); // サーボが動くのを待つ
}
