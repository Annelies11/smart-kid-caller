#include "header.h"

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  //Serial.begin(9600);     // start serial interface
  mp3.begin(9600);        // start mp3-communication
  delay(500);             // wait for init
  mp3.sendCommand(CMD_SEL_DEV, 0, 2);   //select sd-card
  delay(500);             // wait for init
}

void loop() {
  const long interval = 2000;
  if(state != 0){
    state = 0;
    lcd.clear();    
  }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if(msg == 1){
        msg = 2;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tap Kartu");
        lcd.setCursor(0,1);
        lcd.print("Untuk Memanggil");
      } else {
        msg = 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Siswa");
        lcd.setCursor(0,1);
        lcd.print("                ");
      }
    }

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println(content.substring(1));
  if(content.substring(1) == ID[0]){
    Serial.println("Kartu Pertama");
    if(state != 1){
      lcd.clear();
      state = 1;
    }
    lcd.setCursor(0,0);
    lcd.print("Memanggil : ");
    lcd.setCursor(0,1);
    lcd.print("Nehan");
    callKid(1);
    msg = 1;
  }
  if(content.substring(1) == ID[1]){
    Serial.println("Kartu Kedua");
    if(state != 2){
      lcd.clear();
      state = 2;
    }
    lcd.setCursor(0,0);
    lcd.print("Memanggil : ");
    lcd.setCursor(0,1);
    lcd.print("Bima");
    callKid(2);
//    delay(3000);
    msg = 1;
  }
}

void callKid(int ind) {
  int n = 2;
  mp3.play(1);
  delay(2000);
  for(int i = 0; i < n; i++){   
    if(ind == 1){
      mp3.play(7);
      delay(3000);
    } else {
      mp3.play(8);
      delay(3000);
    }
    if(i == 0){
      mp3.play(5);
      delay(3000);
    }
  }
  mp3.play(3);
  delay(3500);
}
