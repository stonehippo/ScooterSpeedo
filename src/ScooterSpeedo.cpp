/*
  A wheel encoder speedometer and accelerometer for the tyke's scooter

  https://github.com/stonehippo/ScooterSpeedo
  
  Components
  
  - Arduino Pro Mini 5v 16mHz
  - Adafruit MMA8451 3-axis 14-bit acceleroemeter https://www.adafruit.com/products/2019
  - Hall effect sensor https://www.adafruit.com/product/158
  - 16x2 LCD character display
  
*/
#include <Arduino.h>

#include "ScooterSpeedo.h"

#include <math.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

// Scooter constants
const double WHEEL_RADIUS = 6.0; // in cm
const double WHEEL_CIRCUMFERENCE = 2 * WHEEL_RADIUS * PI;
double kph = 0.0;
double mph = 0.0;

// Read the max recorded KPH and store it in memory
const int MAX_RECORD_KPH_ADDRESS = 0;
double maxRecordKph = 0.0;

// Read the max recorded forward acceleration, too
const int MAX_RECORD_ACCEL_Y_ADDRESS = 8;
double maxRecordAccelY = 0.0;

// Hall effect sensor read pin, make it an interrupt pin so we catch all revolutions
const byte HALL_SENSOR = 2;
boolean isHallSensorTriggered = false;
double tickCount = 0.0;
double currentMillis = 0.0;
double millisSinceLastTick = 0.0;

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
  pinMode(HALL_SENSOR, INPUT_PULLUP);
  attachInterrupt(0,triggerCount, FALLING);
  
  // Set up the brightness and constrast on the LCD display
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
  lcd.setCursor(0,1);
  lcd.print("Circ: ");
  lcd.print(WHEEL_CIRCUMFERENCE);
  lcd.print("cm");

  delay(2000);
  lcd.clear();
  
  EEPROM.get(MAX_RECORD_KPH_ADDRESS, maxRecordKph);
  if (isnan(maxRecordKph)) {
    maxRecordKph = 0.0;
  }
  
  EEPROM.get(MAX_RECORD_ACCEL_Y_ADDRESS, maxRecordAccelY);
  if (isnan(maxRecordAccelY)) {
    maxRecordAccelY = 0.0;
  }

  lcd.print("Max kph: ");
  lcd.print(maxRecordKph);
  lcd.setCursor(0,1);
  lcd.print("Max mph: ");
  lcd.print(kphToMph(maxRecordKph));
  
  delay(2000);
  lcd.clear();
  
  lcd.print("Max Accel Y: ");
  lcd.setCursor(0,1);
  lcd.print(maxRecordAccelY);
  lcd.print(" m/s^2");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  mma.read();

  /* Get a new sensor event */
  sensors_event_t event;
  mma.getEvent(&event);
  
  lcd.clear();
  
  kph = calculateKPH();
  mph = calculateMPH();
  
  lcd.print(kph);
  lcd.print("kph/");
  lcd.print(mph);
  lcd.print("mph");
  
  lcd.setCursor(0,1);
  lcd.print("AccY:");
  lcd.print(event.acceleration.y);
  lcd.print(" m/s^2");

  if (event.acceleration.y > maxRecordAccelY) {
    maxRecordAccelY = event.acceleration.y;
    noInterrupts();
    setMaxAccelY(maxRecordAccelY);
    interrupts();
  }
  
  // using blocking delay debounces the accelerometer and gives the display time to refresh
  delay(250);
}

// ******************* INTERRUPT EVENTS ******************* 
void triggerCount() {
  tickCount = tickCount + 1.0;
  millisSinceLastTick = millis();
}

// ******************* Speed functions *******************

double calculateKPH() {
  // How many CM per second we've traveled, based on wheel circumference and number of wheel turns since last check
  double cmps =  (1000/(millisSinceLastTick - currentMillis)) * WHEEL_CIRCUMFERENCE * tickCount;
  // reset counts
  tickCount = 0.0;
  currentMillis = millisSinceLastTick;
  if (isnan(cmps)) {
    cmps = 0.0; 
  }
  double k = cmps/10000.0 * 360.0;
  if (k > maxRecordKph) {
    noInterrupts();
    maxRecordKph = k;
    setMaxSpeed(maxRecordKph);
    interrupts();
  }
  return k;
}

double calculateMPH() {
   return kphToMph(kph);
}

double kphToMph(double k) {
  return k * 1.6093;
};

// ******************* Max record functions *******************

void setMaxSpeed(double k) {
  EEPROM.put(MAX_RECORD_KPH_ADDRESS, k); 
}

void setMaxAccelY(double a) {
  EEPROM.put(MAX_RECORD_ACCEL_Y_ADDRESS, a);  
}

void resetRecords() {
  EEPROM.put(MAX_RECORD_KPH_ADDRESS, 0.0);
  EEPROM.put(MAX_RECORD_ACCEL_Y_ADDRESS, 0.0);  
}
