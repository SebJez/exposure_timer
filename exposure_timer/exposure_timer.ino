//PINOUT

#include "config.h"
#include "lcd.h"
#include "relay.h"
#include <RotaryEncoder.h>

Relay relay(P_RELAY);
Display display(P_LCD_RS, P_LCD_EN, P_LCD_D4,P_LCD_D5,P_LCD_D6,P_LCD_D7);
RotaryEncoder encoder(A2, A3);
//pinMode(P_OK, INPUT_PULLUP);
//pinMode(P_LCD_BACKLIGHT, OUTPUT);  //TODO: MOVE TO display.h 



//----TIMER FUNCTIONS----//

int setTimer(int defaultValue=0)
{
  display.clear();
  display.writeTopLine("Czas ekspozycji:");
                      //0123456789ABCDEF
 int seconds = defaultValue;
  display.writeBottomLine(formatTime(seconds,10));
   encoder.setPosition(defaultValue);
  while(digitalRead(P_OK)==HIGH)
  {
    int new_seconds = encoder.getPosition();
    if(new_seconds<0)
    {
      new_seconds = 0;
      encoder.setPosition(0);
    }
    if(new_seconds != seconds)
    {
      seconds = new_seconds;
      display.writeBottomLine(formatTime(seconds,10));
    }
    delay(100);
  }
  display.writeTopLine(formatTime(seconds,10));
  display.bar(1.0);
  delay(1000);
  return seconds;
}

long runTimer(long milliseconds)
{
  long startTime = millis();
  long stopTime = startTime + milliseconds;
  relay.on();

  while(millis() < stopTime)
  {
    long remainingTime = stopTime - millis();
    display.writeTopLine(formatTime(remainingTime/1000+1,10));
    display.bar((float)remainingTime/(float)milliseconds);
    delay(100);
    if(digitalRead(P_OK)==LOW)
    {
      relay.off();
      //                    0123456789ABCDEF
      //display.writeTopLine("      Pauza     ");
      display.writeBottomLine(">Start    Reset");
      encoder.setPosition(0);
      delay(1000);
      int dir;
      int selection = 0;
      while(digitalRead(P_OK)==HIGH)
      {
        dir = encoder.getDirection();
        if(dir ==  1)
        {
           display.writeBottomLine(" Start   >Reset");
           selection = 1;
        }
        else if(dir == -1) 
        {
          display.writeBottomLine(">Start    Reset");
          selection = 0;
        }
        delay(100);
      }
      display.writeBottomLine("");
      delay(1000);
      if(selection == 0)
      {
        relay.on();
        stopTime = millis()+remainingTime;
      }
      else
      {
        relay.off();
        return 0;
      }
      
    }
  }
    
  relay.off();
  display.writeTopLine("");
  display.writeBottomLine("     Gotowe     ");
  //                    0123456789ABCDEF
  while(true)
  {
    analogWrite(P_LCD_BACKLIGHT,200);
    delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    analogWrite(P_LCD_BACKLIGHT,250);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
    if(digitalRead(P_OK)==LOW) break;
        delay(100);
  }
  analogWrite(P_LCD_BACKLIGHT,100);
  display.clear();
  delay(1000);
  return 0;
}

String formatTime(int seconds, int minLength)
{
  String out = "";
  out.reserve(minLength);
  int minutes = seconds/60;
  out += String(minutes);
  out += ":";
  int justseconds = seconds%60;
  if(justseconds<10)
    out += "0";
  out+= String(justseconds);

  while (out.length() < minLength)
  {
    out = " " + out;
  }

  return out;
}
 //------------------------------------------//



void setup() {
  
  analogWrite(9,100);

    PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
    PCMSK1 |= (1 << PCINT10) | (1 << PCINT11);  // This enables the interrupt for pin 2 and 3 of Port C.
  pinMode(P_OK, INPUT_PULLUP);
  
  //long remTime = runTimer(100000);
  delay(100);
//  display.writeTopLine(String(remTime));
}

long last_setting = 0;

void loop() {

  long seconds = setTimer(last_setting);
  last_setting = seconds;
  runTimer(seconds*1000);

}



ISR(PCINT1_vect) {
  encoder.tick(); // just call tick() to check the state.
}
