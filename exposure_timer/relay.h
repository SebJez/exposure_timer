#ifndef relay_h
#define relay_h
#include "config.h"


    #ifdef RELAY_ACTIVE_ON_LOW
        #define REL_ON LOW
        #define REL_OFF HIGH
    #else
        #define REL_ON HIGH
        #define REL_OFF LOW
    #endif




class Relay
{
private:
    const int pin_;
public:
    Relay(int pin);
    inline void on() const;
    inline void off() const;
};




Relay::Relay(int pin) : pin_(pin)
{
    pinMode(pin_,OUTPUT);
}

inline void Relay::on() const
{
    digitalWrite(pin_,REL_ON);
}

inline void Relay::off() const
{
    digitalWrite(pin_,REL_OFF);
}




#endif