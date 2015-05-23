/*
  A wheel encoder speedometer and accelerometer for the tyke's scooter

  https://github.com/stonehippo/ScooterSpeedo
  
  Components
  
  - Arduino Pro Mini 5v 16mHz
  - Adafruit MMA8451 3-axis 14-bit acceleroemeter https://www.adafruit.com/products/2019
  - Hall effect sensor https://www.adafruit.com/product/158
  - 16x2 LCD character display
  
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>


// 16x2 LCD display pins
const byte LCD_BACKLIGHT = 5;
const byte LCD_CONTRAST = 6;

/*
 * LCD RS pin to D13
 * LCD Enable pin D12
 * LCD D4 pin to D8
 * LCD D5 pin to D9
 * LCD D6 pin to D10
 * LCD D7 pin to D11
 */
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {
  pinMode(LCD_CONTRAST, OUTPUT);
  pinMode(LCD_BACKLIGHT, OUTPUT);
  analogWrite(LCD_BACKLIGHT, 40);
  analogWrite(LCD_CONTRAST, 120);

  lcd.begin(16,2);

  if (! mma.begin()) {
    lcd.print("No accel start");
    while (1);
  }
  mma.setRange(MMA8451_RANGE_8_G);
  lcd.print("Ready!");
}

void loop() {
  mma.read();

  /* Get a new sensor event */
  sensors_event_t event;
  mma.getEvent(&event);

  lcd.clear();

  lcd.print("Current Accel.");
  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.print(event.acceleration.y);
  lcd.print(" m/s^2");
  delay(250);
}
