//PINOUT

#include "pinout.h"
#include "lcd.h"
#include "relay.h"


Relay relay(P_RELAY);
Display display(P_LCD_RS, P_LCD_EN, P_LCD_D4,P_LCD_D5,P_LCD_D6,P_LCD_D7);



void setup() {

}

void loop() {
for(float i = 0; i < 1; i+=0.02)
{
  display.bar(i);
  delay(100);
}

}
