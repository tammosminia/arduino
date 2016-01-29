//using DFRobot.com libraries
//Compatible with the Arduino IDE 1.0
//Library version:1.1

#include <Wire.h>
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);

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
  printLcd(0, 0, "opstarten....");
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

