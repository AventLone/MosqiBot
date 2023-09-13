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

// class UnoTalker
// {
enum UnoCommand : int
{
    UNO_INIT,
    UNO_GLOBAL,
    UNO_LOCAL,
    // DO_NOTHING
};

inline void globCamera()
{
    globLightOn();
    localLightOff();
    Serial2.write(UnoCommand::UNO_GLOBAL);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    while (!Serial2.available())
    {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    Serial.readBytes(buffer, Serial2.available());
    // Serial.readBytes(buffer, Serial2.available());
}

inline void localCamera()
{
    globLightOff();
    localLightOn();
    // local();
    Serial2.write(UnoCommand::UNO_LOCAL);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    while (!Serial2.available())
    {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    Serial.readBytes(buffer, Serial2.available());
    // Serial.readBytes(buffer, Serial2.available());
}

inline void initCamera()
{
    globLightOff();
    localLightOff();
    // init();
    Serial2.write(UnoCommand::UNO_INIT);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    while (!Serial2.available())
    {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    Serial.readBytes(buffer, Serial2.available());
    // Serial.readBytes(buffer, Serial2.available());
}