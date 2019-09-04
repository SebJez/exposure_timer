#include <LiquidCrystal.h>
#include "pinout.h"

namespace characters
{
    byte zero[8] = {0,0,0,0,0,0,0,0};
    byte one[8] =  {1,1,1,1,1,1,1,1};
    byte two[8] =  {3,3,3,3,3,3,3,3};
    byte three[8]= {7,7,7,7,7,7,7,7};
    byte four[8] = {15,15,15,15,15,15,15,15};
    byte five[8] = {31,31,31,31,31,31,31,31};
    byte l[8] ={
        b01100,
        b00100,
        b00110,
        b00100,
        b01100,
        b00100,
        b11111,
        b00000
    }
} // namespace characters

LiquidCrystal lcd(P_LCD_RS,P_LCD_EN,P_LCD_D4,P_LCD_D5,P_LCD_D6,P_LCD_D7);

lcd.createChar(0,characters::zero);
lcd.createChar(1,characters::one);
lcd.createChar(2,characters::two);
lcd.createChar(3,characters::three);
lcd.createChar(4,characters::four);
lcd.createChar(5,characters::five);
lcd.createChar(6,characters::l);

void bar(float value)
{
    int bars = value*80;
    if(bars < 0) bars = 0;
    else if(bars > 80) bars =80;
    lcd.setCursor(1,0);
    for(int i = 0; i < bars/5; i++)
        lcd.write(byte(5));
    lcd.write(byte(bars%5));
}
