#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
 
SoftwareSerial mySerial(2, 3); // RX, TX
 
//
void setup () {
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (15);
}
 
//
void loop () {        
  mp3_play (1);
  delay (6000);
  mp3_play (2);
  delay (6000);
  mp3_play (3);
  delay (6000);
}
