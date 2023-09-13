#pragma once
#include <Servo.h>

Servo gLureServo;

namespace LureDevice
{
inline void fanOn()
{
    digitalWrite(FAN_PIN, HIGH);
}
inline void fanOff()
{
    digitalWrite(FAN_PIN, LOW);
}

inline void mosquitokillerOn()
{
    digitalWrite(MOSQUITO_KILLER_PIN, HIGH);
}
inline void mosquitokillerOff()
{
    digitalWrite(MOSQUITO_KILLER_PIN, LOW);
}

inline void outletOpen()
{
    gLureServo.write(0);
}
inline void outletClose()
{
    gLureServo.write(180);
}
}   // namespace LureDevice
