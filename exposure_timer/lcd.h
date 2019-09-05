#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>
#include "config.h"
class Display
{
public:
    Display(int rs, int en, int d4, int d5, int d6, int d7);
    LiquidCrystal lcd;
    void bar(float value);

private:
    String topline =     "                ";
    String bottomline =  "                ";

    byte zero[8] = {0,0,0,0,0,0,0,0};
    byte one[8] =  {1,1,1,1,1,1,1,1};
    byte two[8] =  {3,3,3,3,3,3,3,3};
    byte three[8]= {7,7,7,7,7,7,7,7};
    byte four[8] = {15,15,15,15,15,15,15,15};
    byte five[8] = {31,31,31,31,31,31,31,31};
};

Display::Display(int rs, int en, int d4, int d5, int d6, int d7)
{
    lcd = LiquidCrystal(rs,en,d4,d5,d6,d7);
    lcd.createChar(0,zero);
    lcd.createChar(1,one);
    lcd.createChar(2,two);
    lcd.createChar(3,three);
    lcd.createChar(4,four);
    lcd.createChar(5,five);
    lcd.begin(16,2);
}



void Display::bar(float value)
{
    int bars = value*80;
    if(bars < 0) bars = 0;
    else if(bars > 80) bars =80;
    lcd.clear();
    lcd.writeTopLine(topline);
    lcd.setCursor(1,0);
    for(int i = 0; i < bars/5; i++)
        lcd.write(byte(5));
    lcd.write(byte(bars%5));
}  


#endif