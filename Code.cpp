## Arduino Code

```cpp
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int totalDays = 100;

const byte uidList[7][4] = {
  {0x43, 0x26, 0x6A, 0x05},
  {0x7C, 0x12, 0x6B, 0x05},
  {0x73, 0x1D, 0x02, 0x04},
  {0x32, 0xD3, 0x01, 0x04},
  {0x63, 0x5E, 0x01, 0x04},
  {0x62, 0x7D, 0x02, 0x04},
  {0xE6, 0x4E, 0x02, 0x04}
};

String names[7] = {
  "Sreevaani", "Himanshu", "Aniket", 
  "Aditya", "Ani", "Keshav", "Priyanshu"
};

String rolls[7] = {
  "23UELEC005", "23UELEC012", "23UELEC004",
  "23UELEC003", "23UELEC002", "23UELEC013", "23UELEC019"
};

String sems[7] = {
  "5", "5", "5", "5", "5", "5", "5"
};

int presentCounts[7] = {0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  lcd.init();
  lcd.backlight();

  setTime(11, 00, 0, 27, 01, 2026); // Simulated time

  // PLX-DAQ setup
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Name,Roll,Semester,Date,Time,Classes Attended,Attendance %");
  Serial.println("RESETTIMER");

  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card Detected");
  delay(1000);

  int index = getCardIndex(rfid.uid.uidByte, rfid.uid.size);

  if (index != -1) {
    presentCounts[index]++;
    float percentage = (presentCounts[index] * 100.0) / totalDays;

    logToExcel(index, percentage);
    showAttendance(names[index], rolls[index], sems[index], percentage, presentCounts[index]);

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unknown Card");

    Serial.print("Unknown UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");

  rfid.PICC_HaltA();
}

int getCardIndex(byte *uid, byte len) {
  for (int i = 0; i < 7; i++) {
    bool match = true;
    for (byte j = 0; j < len; j++) {
      if (uid[j] != uidList[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return i;
  }
  return -1;
}

void logToExcel(int index, float percentage) {
  char dateStr[11];
  char timeStr[9];

  sprintf(dateStr, "%02d/%02d/%04d", day(), month(), year());
  sprintf(timeStr, "%02d:%02d:%02d", hour(), minute(), second());

  Serial.print("DATA,");
  Serial.print(names[index]); Serial.print(",");
  Serial.print(rolls[index]); Serial.print(",");
  Serial.print(sems[index]); Serial.print(",");
  Serial.print(dateStr); Serial.print(",");
  Serial.print(timeStr); Serial.print(",");
  Serial.print(presentCounts[index]); Serial.print(",");
  Serial.println((int)percentage);
}

void showAttendance(String name, String roll, String sem, float percentage, int attendedClasses) {
  char dateStr[17];
  sprintf(dateStr, "%02d/%02d/%04d", day(), month(), year());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(name);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Roll:");
  lcd.setCursor(6, 0);
  lcd.print(roll);
  lcd.setCursor(0, 1);
  lcd.print("Sem:");
  lcd.setCursor(5, 1);
  lcd.print(sem);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Attendance:");
  lcd.setCursor(0, 1);
  lcd.print(String((int)percentage) + "%");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date:");
  lcd.setCursor(6, 0);
  lcd.print(dateStr);
  delay(1000);
}
```
