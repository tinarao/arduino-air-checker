#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define DHTpin 12
#define infoled 9

DHT dht(DHTpin, DHT11);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();                     
  lcd.backlight();

  pinMode(infoled, OUTPUT);

  Serial.begin(9600);
  dht.begin();
}

void loop() {

  digitalWrite(infoled, HIGH);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Ошибка считывания");
    // digitalWrite(infoled, LOW);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(t);
  lcd.write(223);

  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(h);
  lcd.print("%");

  delay(10000);
}