#ifndef lcd_h
#define lcd_h

#include <LiquidCrystal.h>
#include "config.h"
class Display
{
public:
    Display(int rs, int en, int d4, int d5, int d6, int d7);
    LiquidCrystal* lcd;
    void bar(float value);
    inline void writeTopLine(String text);
    inline void writeBottomLine(String text);
    inline void clear();
private:
    byte zero[8] = {0,0,0,0,0,0,0,0};         //b00000
    byte one[8] =  {16,16,16,16,16,16,16,16}; //b10000
    byte two[8] =  {24,24,24,24,24,24,24,24}; //b11000
    byte three[8]= {28,28,28,28,28,28,28,28}; //b11100
    byte four[8] = {30,30,30,30,30,30,30,30}; //b11110
    byte five[8] = {31,31,31,31,31,31,31,31}; //b11111
};

Display::Display(int rs, int en, int d4, int d5, int d6, int d7)
{
    lcd = new LiquidCrystal(rs,en,d4,d5,d6,d7);
    lcd->createChar(0,zero);
    lcd->createChar(1,one);
    lcd->createChar(2,two);
    lcd->createChar(3,three);
    lcd->createChar(4,four);
    lcd->createChar(5,five);
    lcd->begin(16,2);
}



void Display::bar(float value)
{
    int bars = value*80;
    if(bars < 0) bars = 0;
    else if(bars > 80) bars =80;
    lcd->setCursor(0,1);
    for(int i = 0; i < bars/5; i++)
        lcd->write(byte(5));
    lcd->write(byte(bars%5));
    for(int i = 15; i>  bars/5; i--)
        lcd->print(" ");
}

inline void Display::writeTopLine(String text)
{
    lcd->setCursor(0,0);
    lcd->print(text);
    for(int i = text.length(); i<16; i++)
        lcd->print(" ");
}

inline void Display::writeBottomLine(String text)
{
    lcd->setCursor(0,1);
    lcd->print(text);
    for(int i = text.length(); i<16; i++)
        lcd->print(" ");
}
inline void Display::clear()
{
    lcd->clear();
}
#endif
