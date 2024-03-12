/*
RFID
RST     ==  9
MISO    ==  12
MOSI    ==  11
SCK     ==  13
SDA     ==  10

MP3 
TX      ==  4
RX      ==  5
*/

#include <SPI.h>
#include <MFRC522.h>
#include "SerialMP3Player.h"

#define TX 4
#define RX 5
SerialMP3Player mp3(RX,TX);

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

String ID[] = {"d3 dc fc 0f", "73 5a ff 0d"};
uint8_t state = 0;
unsigned long previousMillis = 0;
uint8_t msg = 1;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
