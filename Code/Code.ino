/*
====================================================
  CLASSROOM NOISE MONITORING SYSTEM – ESP8266
====================================================

Nodemcu Connections:
D1 -> SCL (LCD)
D2 -> SDA (LCD)
D3 -> RST (RFID)
D4 -> SDA (RFID)
D5 -> SCK
D6 -> MOSI
D7 -> MISO
D8 -> BUZZER (+)
====================================================
*/

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// ---------------- PIN DEFINITIONS ----------------
#define SS_PIN   2   // D4
#define RST_PIN  0   // D3
#define BUZZER   15  // D8
// -------------------------------------------------

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- RFID → CLASS MAPPING ----------------
struct ClassCard {
  String uid;
  String className;
};

ClassCard cards[] = {
  {"d3f62429", "Class 10-A"},
  {"f3145a28", "Class 9-B"},
  {"a1b2c3d4", "Class 8-C"}
};

const int TOTAL_CARDS = sizeof(cards) / sizeof(cards[0]);
// -----------------------------------------------------

// ---------------- GLOBAL VARIABLES ----------------
bool teacherPresent = false;
String currentClass = "No Class";
String db_data = "0";
String scanID = "";
// --------------------------------------------------

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // LCD INIT
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Class Noise");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");
  delay(2000);
  lcd.clear();

  // RFID INIT
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {

  // ---------- LCD DISPLAY ----------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentClass);
  lcd.setCursor(0, 1);

  if (teacherPresent) {
    lcd.print("P ");
  } else {
    lcd.print("A ");
  }

  lcd.print(db_data);
  lcd.print("db");

  delay(400);

  // ---------- SERIAL DATA FROM WEBSITE ----------
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    // Normal decibel update
    if (msg.startsWith("N:")) {
      db_data = msg.substring(2);
      digitalWrite(BUZZER, LOW);
    }

    // Noise alert
    if (msg.startsWith("A:")) {
      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
    }
  }

  // ---------- RFID CARD DETECTION ----------
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  scanID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    scanID += String(rfid.uid.uidByte[i], HEX);
  }
  scanID.toLowerCase();

  Serial.println("RFID:" + scanID);

  bool matched = false;

  for (int i = 0; i < TOTAL_CARDS; i++) {
    if (scanID == cards[i].uid) {
      matched = true;

      // Toggle teacher presence
      teacherPresent = !teacherPresent;
      currentClass = cards[i].className;

      // Beep confirmation
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(BUZZER, LOW);

      break;
    }
  }

  if (!matched) {
    Serial.println("Unknown RFID Card");
  }

  scanID = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
