#include <Keyboard.h>
#include <Mouse.h>
#include "Keydefine.h"
// Left : 0 Right : 1
const byte thisSide = 0;
//const int rowNum = 5;
//const int colNum = 5;
//const int rowPin[rowNum] = { 2, 3, 4, 5, 6 };
//const int colPin[colNum] = { 7, 8, 9, 10, 16};
//const byte keyMap[rowNum*2][colNum] = {
// LeftSide
//  { KC_1, KC_2, KC_3, KC_4, KC_5},
// { KC_Q, KC_W, KC_E, KC_R, KC_T},
// { KC_A, KC_S, KC_D, KC_F, KC_G},
// { KC_Z, KC_X, KC_C, KC_V, KC_B},
//{ KC_LALT, KC_LGUI, KC_LSFT, KC_SPC, NONE},
// RightSide
// { KC_6, KC_7, KC_8, KC_9, KC_0},
// {KC_Y, KC_U, KC_I, KC_O, KC_P},
// {KC_H, KC_J, KC_K, KC_L, KC_SCLN},
// {KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH},
// {NONE, KC_BSPC, KC_ENT, KC_RGUI, KC_BSLS}
//};

const int rowNum = 4;
const int colNum = 6;
const int rowPin[rowNum] = { 4, 5, 6, 7 };
const int colPin[colNum] = { 8, 9, 10, 16, 14, 15};
const byte keyMap[rowNum * 2][colNum] = {
  // LeftSide
  //KC_TAB, KC_CAPS, KC_LSFT, NONE,
  {KC_Q, KC_W, KC_E, KC_R, KC_T},
  {KC_A, KC_S, KC_D, KC_F, KC_G},
  {KC_Z, KC_X, KC_C, KC_V, KC_B},
  {KC_LALT, KC_LCTL, KC_LSFT, KC_CAPS, KC_SPC},
  // RightSide
  //, KC_EQL , KC_QUOT , KC_MINS , NONE KC_BSLS KC_RGUI KC_BSPC
  {KC_Y, KC_U, KC_I, KC_O, KC_P},
  {KC_H, KC_J, KC_K, KC_L, KC_SCLN},
  {KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH},
  {KC_BSPC, KC_ENT, KC_RSFT, KC_RCTL, KC_RALT}
};

const byte keyMap2[rowNum * 2][colNum] = {
  // LeftSide
  //KC_TAB, KC_CAPS, KC_LSFT, NONE,
  {KC_Q, KC_W, KC_E, KC_R, KC_T},
  {KC_A, KC_S, KC_D, KC_F, KC_G},
  {KC_Z, KC_X, KC_C, KC_V, KC_B},
  {KC_LALT, KC_LCTL, KC_LSFT, KC_CAPS, KC_SPC},
  // RightSide
  //, KC_EQL , KC_QUOT , KC_MINS , NONE KC_BSLS KC_RGUI KC_BSPC
  {KC_Y, KC_U, KC_I, KC_O, KC_P},
  {KC_H, KC_J, KC_K, KC_L, KC_SCLN},
  {KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH},
  {KC_BSPC, KC_ENT, KC_RSFT, KC_RCTL, KC_RALT}
};

const byte keyMap3[rowNum * 2][colNum] = {
  // LeftSide
  //KC_TAB, KC_CAPS, KC_LSFT, NONE,
  {KC_7, KC_8, KC_9, KC_R, KC_T},
  {KC_4, KC_5, KC_6, KC_F, KC_G},
  {KC_1, KC_2, KC_3, KC_V, KC_B},
  {KC_LALT, KC_LCTL, KC_LSFT, KC_CAPS, KC_SPC},
  // RightSide
  //, KC_EQL , KC_QUOT , KC_MINS , NONE KC_BSLS KC_RGUI KC_BSPC
  {KC_Y, KC_U, KC_I, KC_O, KC_P},
  {KC_H, KC_J, KC_K, KC_L, KC_SCLN},
  {KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH},
  {KC_BSPC, KC_ENT, KC_RSFT, KC_RCTL, KC_RALT}
};

bool currentState[rowNum][colNum];
bool beforeState[rowNum][colNum];
int i, j, row, isPress;
byte sendData, readData;
bool isMouse;
byte pressKey;

//初期化
void setup() {
  for ( i = 0; i < rowNum; i++) {
    pinMode(rowPin[i], OUTPUT);
    digitalWrite(rowPin[i], HIGH);
  }

  for ( i = 0; i < colNum; i++) {
    pinMode(colPin[i], INPUT_PULLUP);
  }

  for ( i = 0; i < rowNum; i++) {
    for ( j = 0; j < colNum; j++) {
      currentState[i][j] = HIGH;
      beforeState[i][j] = HIGH;
    }
  }
  Serial.begin(9600);
  Serial1.begin(9600);
  Keyboard.begin();
  Mouse.begin();
  isMouse = false;

}


void loop() {
  for ( i = 0; i < rowNum; i++) {
    digitalWrite( rowPin[i], LOW );
    row = i + 4 * thisSide;
    for ( j = 0; j < colNum; j++) {
      currentState[i][j] = digitalRead(colPin[j]);

      if ( currentState[i][j] != beforeState[i][j] ) {

        Serial.print("key(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.print(")");

        if ( currentState[i][j] == LOW) {
          isPress = 1;
          Serial.println(" Push!");
          Serial.println(keyMap[row][j]);
          Keyboard.press( keyMap[row][j] );

          if ( keyMap[row][j] == keyMap[0][0]) {
            isMouse = true;
            Mouse.move(1, 0, 0);
          }

          if ( keyMap[row][j] == keyMap[0][1]) {
            isMouse = false;
          }

          pressKey =  keyMap[row][j];

        } else {
          isPress = 0;
          Serial.println(" Release!");
          Serial.println(keyMap[row][j]);
          Keyboard.release( keyMap[row][j] );
    pressKey = "";
        }
        beforeState[i][j] = currentState[i][j];
        sendData = isPress << 6 | row << 3 | j;
        Serial1.write(sendData);
        Serial.println("送る");
        Serial.println(sendData, BIN);
        Serial.println(row);
        Serial.println(j);
        //Mouse.click();

      }



    }
    digitalWrite( rowPin[i], HIGH );


  }
  if (Serial1.available()) {
    readSerial();
  }


  if ( isMouse == true) {
    if ( pressKey == keyMap[0][2]) {
      Mouse.move(0, -1, 0);
          delay(2);
    }
    if ( pressKey == keyMap[1][1]) {
      Mouse.move(-1, 0, 0);
          delay(2);
    }

    if ( pressKey == keyMap[1][2]) {
      Mouse.move(0, 1, 0);
          delay(2);
    }
    if ( pressKey == keyMap[1][3]) {
      Mouse.move(1, 0, 0);
          delay(2);
    }
  }




}

void readSerial() {
  int keyRow, keyCol;
  readData = Serial1.read();
  Serial.println(readData);
  Serial.println(readData, BIN);

  if ( readData & 0b10000000 ) {
  } else {
    isPress = readData >> 6;
    keyRow = readData & 0b00111000;
    keyRow = keyRow >> 3;
    keyCol = readData & 0b00000111;
    Serial.println(readData & 0b00111000, BIN);
    Serial.println(readData & 0b00111000 >> 3, BIN);

    if ( isPress ) {
      Keyboard.press( keyMap[keyRow][keyCol] );
      Serial.print("key(");
      Serial.print(keyRow);
      Serial.print(",");
      Serial.print(keyCol);
      Serial.print(")");


    } else {
      Keyboard.release( keyMap[keyRow][keyCol] );
      Serial.print("key(");
      Serial.print(keyRow);
      Serial.print(",");
      Serial.print(keyCol);
      Serial.print(")");
    }
  }
}
