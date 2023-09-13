#pragma once

uint8_t buffer[10] = {0};

/*** Control global and local light ***/
inline void globLightOn()
{
    digitalWrite(GLOB_LIGHT_PIN, HIGH);
}
inline void globLightOff()
{
    digitalWrite(GLOB_LIGHT_PIN, LOW);
}
inline void localLightOn()
{
    digitalWrite(LOCAL_LIGHT_PIN, HIGH);
}
inline void localLightOff()
{
    digitalWrite(LOCAL_LIGHT_PIN, LOW);
}
/**************************************/

namespace camera
{
enum UnoCommand : int
{
    CAMERA_INIT_ZOOM,
    CAMERA_INIT_FOCUS,
    CAMERA_INIT_OVER,
    CAMERA_GLOBAL,
    CAMERA_LOCAL_1,
    CAMERA_LOCAL_2,
    CAMERA_LOCAL_3
};

void global()
{
    globLightOn();
    localLightOff();
    Serial2.write(UnoCommand::CAMERA_GLOBAL);
    delay(3000);
    while (!Serial2.available())
    {
        delay(2000);
    }

    Serial.readBytes(buffer, Serial2.available());
}

void local_1()
{
    globLightOff();
    localLightOn();
    Serial2.write(UnoCommand::CAMERA_LOCAL_1);
    delay(3000);
    while (!Serial2.available())
    {
        delay(2000);
    }

    Serial.readBytes(buffer, Serial2.available());
}
void local_2()
{
    // globLightOff();
    // localLightOn();
    Serial2.write(UnoCommand::CAMERA_LOCAL_2);
    delay(3000);
    while (!Serial2.available())
    {
        delay(2000);
    }

    Serial.readBytes(buffer, Serial2.available());
}
void local_3()
{
    // globLightOff();
    // localLightOn();
    Serial2.write(UnoCommand::CAMERA_LOCAL_3);
    delay(3000);
    while (!Serial2.available())
    {
        delay(2000);
    }

    Serial.readBytes(buffer, Serial2.available());
}

void init()
{
    globLightOff();
    localLightOff();
    // init();
    Serial2.write(UnoCommand::CAMERA_INIT_ZOOM);
    while (digitalRead(CAMERA_ZOOM_LIMIT) == LOW)
    {
        delay(10);
    }
    Serial2.write(UnoCommand::CAMERA_INIT_FOCUS);
    while (digitalRead(CAMERA_FOCUS_LIMIT) == LOW)
    {
        delay(10);
    }
    Serial2.write(UnoCommand::CAMERA_INIT_OVER);
    delay(100);

    // delay(3000);
    // while (!Serial2.available())
    // {
    //     delay(2000);
    // }
    // Serial.readBytes(buffer, Serial2.available());
}
}