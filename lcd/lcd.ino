//This will measure the current light level and show it on LCD.
//It will also keep a record of minimum and maximum level and show that on the LCD
//This is perfect for checking if the fridge light goes off when you close the door.
//The startup where it counts to 3000 ms is just for show; not necessary at all :)

#include <Wire.h>
//The library, in combination with arduino IDE 1.6.7 has a bug. 
//When using lcd.print, it prints only the first letter
#include <LiquidCrystal_I2C.h>

//schematic:
//lcd(with I2C) on sda, scl, +, -
//photosensor on a0 (and + and - with a 10k ohm resistor)

LiquidCrystal_I2C lcd(0x27, 16, 2);

void printLcd(int x, int y, String s) {
  Serial.println("printing" + s);
  for (int index = 0; index < s.length(); ++index) {
    lcd.setCursor(x + index, y);
    lcd.print(s[index]);
  }
}

void printLcd(int x, int y, int i) {
  char *intStr = "1234567890123456";
  sprintf(intStr, "%i", i);
  printLcd(x, y, intStr);
}

void setup(){
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  printLcd(0, 0, "starting....");
  while(millis() < 3000) {
    printLcd(0, 1, millis());    
  }
}

int backlightState = LOW;
long previousMillis = 0;
long interval = 1000;
int smin = -1;
int smax = -1;
  
void loop(){
  int sensorValue = analogRead(0);
  if (smin == -1 || sensorValue < smin) smin = sensorValue;
  if (smax == -1 || sensorValue > smax) smax = sensorValue;
  
//  lcd.clear();
  Serial.println(sensorValue);
  char *line = "1234567890123456";
  sprintf(line, "min:%i max:%i        ", smin, smax);
  printLcd(0, 0, line);
  sprintf(line, "%i                   ", sensorValue);
  printLcd(0, 1, line);
  
  delay(100);
}

