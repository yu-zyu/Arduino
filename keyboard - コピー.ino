#include <Keyboard.h>
#include "Keydefine.h"
// Left : 0 Right : 1
const byte thisSide = 0;
const int rowNum = 4;
const int colNum = 6;
const int rowPin[rowNum] = { 3, 4, 11, 12 };
const int colPin[colNum] = { 5, 6, 7, 8, 9, 10 };
const byte keyMap[rowNum*2][colNum] = {
 // LeftSide
 {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T},
 {KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G},
 {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B},
 {NONE, KC_LALT, KC_LGUI, KC_LSFT, KC_SPC, NONE},
 // RightSide
 {KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL},
 {KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
 {KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS},
 {NONE, KC_BSPC, KC_ENT, KC_RGUI, KC_BSLS, NONE}
};
bool currentState[rowNum][colNum];
bool beforeState[rowNum][colNum];
int i,j,row,isPress;
byte sendData,readData;

void setup() {
 for( i = 0; i < rowNum; i++){
 pinMode(rowPin[i],OUTPUT);
 digitalWrite(rowPin[i],HIGH);
 }

 for( i = 0; i < colNum; i++){
 pinMode(colPin[i],INPUT_PULLUP);
 }

 for( i = 0; i < rowNum; i++){
 for( j = 0; j < colNum; j++){
 currentState[i][j] = HIGH;
 beforeState[i][j] = HIGH;
 }
 }
 Serial.begin(9600);
 Serial1.begin(9600);
 Keyboard.begin(); }
void loop() {
 for( i = 0; i < rowNum; i++){
 digitalWrite( rowPin[i], LOW );
 row = i + 4 * thisSide;
 for( j = 0; j < colNum; j++){
 currentState[i][j] = digitalRead(colPin[j]);

 if ( currentState[i][j] != beforeState[i][j] ){

 Serial.print("key(");
 Serial.print(i);
 Serial.print(",");
 Serial.print(j);
 Serial.print(")");

 if ( currentState[i][j] == LOW){
 isPress = 1;
 Serial.println(" Push!");
 Keyboard.press( keyMap[row][j] );
 } else {
 isPress = 0;
 Serial.println(" Release!");
 Keyboard.release( keyMap[row][j] );
 }
 beforeState[i][j] = currentState[i][j];
 sendData = isPress << 6 | row << 3 | j;
 Serial1.write(sendData);
 }
 }
 digitalWrite( rowPin[i], HIGH );
 }
 if(Serial1.available()){
 readSerial();
 } }
void readSerial(){
 int keyRow, keyCol;
 readData = Serial1.read();
 Serial.println(readData);

 if ( readData & 0b10000000 ){
 } else {
 isPress = readData >> 6;
 keyRow = readData & 0b00111000 >> 3;
 keyCol = readData & 0b00000111;

 if( isPress ){
 Keyboard.press( keyMap[keyRow][keyCol] );
 } else {
 Keyboard.release( keyMap[keyRow][keyCol] );
 }
 } }
