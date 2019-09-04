//PINOUT

#include "pinout.h"
#include "lcd.h"

volatile bool timer = false;

void checkCover()
{
  
  if(digitalRead(P_MSWITCH)==LOW)
  {
    digitalWrite(P_RELAY, REL_OFF);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Os");
    lcd.write(byte(6));
    lcd.print("ona otwarta");
  }
  while(digitalRead(P_MSWITCH)==LOW)
  {
    delay(100)
  }
  
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(P_MSWITCH, INPUT_PULLUP);
  pinMode(P_OK, INPUT_PULLUP);
  pinMode(P_RELAY,OUTPUT);
  pinMode(P_LCD_BACKLIGHT,OUTPUT);

  digitalWrite(P_RELAY, REL_OFF);

}

void loop() {
  checkCover();

}
