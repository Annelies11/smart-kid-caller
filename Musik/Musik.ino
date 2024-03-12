#include "SerialMP3Player.h"

#define TX 4
#define RX 5

SerialMP3Player mp3(RX,TX);

void setup() {
  Serial.begin(9600);     // start serial interface
  mp3.begin(9600);        // start mp3-communication
  delay(500);             // wait for init

  mp3.sendCommand(CMD_SEL_DEV, 0, 2);   //select sd-card
  delay(500);             // wait for init
}

// the loop function runs over and over again forever
void loop() {
  mp3.play(8);     // Play "hello.mp3". You must hear "Hello World"
  delay(3000);    // wait 3 seconds
  /*
  1 Panggilan
  3 Ditunggu
  5 Sekali
  7 Nehan
  8 
  */
  
}
