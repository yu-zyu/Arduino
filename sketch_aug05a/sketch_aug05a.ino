#include <NewSoftSerial.h>
const int rxpin = 2; // pin used to receive from GPS
const int txpin = 3; // pin used to send to GPS
NewSoftSerial serial_gps(txpin, rxpin); // new serial port on pins 2 and 3
void setup()
{
Serial.begin(9600); // 9600 baud for the built-in serial port
serial_gps.begin(4800); // initialize the port, most GPS devices use 4800 baud
}
void loop()
{
if (serial_gps.available() > 0) // any character arrived yet?
{
char c = serial_gps.read(); // if so, read it from the GPS
Serial.print(c, BYTE); // and echo it to the serial console
}
