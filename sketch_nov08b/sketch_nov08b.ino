#define STX A1
#define STY A0
const byte stk_pins [2] = {STX, STY};
void setup() {
for (byte i = 0 ; i < 2 ; i++) pinMode(stk_pins[i], INPUT);
Serial.begin(38400);
}
void loop() {
Serial.print("X:");
Serial.print(analogRead(stk_pins[0]));
Serial.print("  Y:");
Serial.print(analogRead(stk_pins[1]));
Serial.println();
}
