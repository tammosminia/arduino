//This will measure the current light level and show it on LCD.
//It will also keep a record of minimum and maximum level and show that on the LCD
//This is perfect for checking if the fridge light goes off when you close the door.
//The startup where it counts to 3000 ms is just for show; not necessary at all :)

#include <Wire.h>
//The library, in combination with arduino IDE 1.6.7 has a bug. 
//When using lcd.print, it prints only the first letter
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>


//schematic:
//lcd(with I2C) on sda, scl, +, -
//photosensor on a0 (and + and - with a 10k ohm resistor)

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
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
  irrecv.enableIRIn(); // Start the receiver

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  printLcd(0, 0, "starting....");
  while(millis() < 1000) {
    printLcd(0, 1, millis());    
  }
  printLcd(0, 0, "ready. start adding!");
  printLcd(0, 1, 0);
}

int irCodeToNumber(unsigned long irCode) {
  if (irCode == 0xFF30CF) return 1;
  else if (irCode == 0xFF18E7) return 2;
  else if (irCode == 0xFF7A85) return 3;
  else if (irCode == 0xFF10EF) return 4;
  else if (irCode == 0xFF38C7) return 5;
  else if (irCode == 0xFF5AA5) return 6;
  else if (irCode == 0xFF42BD) return 7;
  else if (irCode == 0xFF4AB5) return 8;
  else if (irCode == 0xFF52AD) return 9;
  else if (irCode == 0xFF9867) return 100;
  else if (irCode == 0xFFB04F) return 200;
  else return 0;
}

int total = 0;
  
void loop(){
  decode_results results;

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    int number = irCodeToNumber(results.value);
    Serial.println(number);
    total += number;
    lcd.clear();
    printLcd(0, 0, number);
    printLcd(0, 1, total);
    irrecv.resume(); // Receive the next value
  }
  
  delay(100);
}

