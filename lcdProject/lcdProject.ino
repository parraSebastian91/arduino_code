
// Arduino with PCF8574T I2C LCD example
 
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
 
void setup() {
 
  lcd.init();                        // Initialize I2C LCD module
 
  lcd.backlight();                   // Turn backlight ON
 
  lcd.setCursor(0, 0);               // Go to column 0, row 0
  lcd.print("010101019123456789012345678901011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
//  lcd.setCursor(0, 1);               // Go to column 0, row 1
//  lcd.print("Mucho <3");
 
}
 
void loop() {
 
}
