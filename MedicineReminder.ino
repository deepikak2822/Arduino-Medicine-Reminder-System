#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

RTC_DS3231 rtc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SoftwareSerial dfSerial(8, 9);
DFRobotDFPlayerMini player;

int remindHour = 9;
int remindMinute = 30;

bool played = false;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);

  if (!rtc.begin()) {
    lcd.print("RTC Error");
    while (1);
  }

  // For testing only
 // rtc.adjust(DateTime(2026, 6, 16, 9, 29, 0));

  dfSerial.begin(9600);
  delay(3000);

  player.begin(dfSerial);   // No DF Error check
  player.volume(30);

  lcd.clear();
  lcd.print("System Ready");
  delay(2000);
}

void loop() {

  DateTime now = rtc.now();

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Time ");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());

  lcd.print(":");

  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());

  lcd.print(":");

  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  lcd.setCursor(0, 1);
  lcd.print("Medicine Sys");

  if (now.hour() == remindHour &&
      now.minute() == remindMinute &&
      !played) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TAKE UR MEDICINE");

    lcd.setCursor(0, 1);
    lcd.print("NOW");

    player.play(1);

    played = true;
    delay(5000);
  }

  if (now.minute() != remindMinute) {
    played = false;
  }

  delay(1000);
}
