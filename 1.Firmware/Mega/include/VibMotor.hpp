#pragma once

class VibMotor
{
public:
    VibMotor();
    void activate(unsigned char signal);

private:
    void on(uint8_t index);
    inline void off()
    {
        digitalWrite(MOTOR_0, LOW);
        digitalWrite(MOTOR_1, LOW);
        digitalWrite(MOTOR_2, LOW);
        digitalWrite(MOTOR_3, LOW);
        digitalWrite(MOTOR_4, LOW);
    }
};

VibMotor::VibMotor()
{
    pinMode(MOTOR_0, OUTPUT);
    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    pinMode(MOTOR_3, OUTPUT);
    pinMode(MOTOR_4, OUTPUT);
}

void VibMotor::activate(unsigned char signal)
{
    unsigned char temp = 1;
    uint8_t j = 0;
    for (uint8_t i = 0; i < 5; ++i)
    {
        if (temp & signal)
        {
            on(j);
        }
        ++j;
        temp <<= 1;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    off();
}

void VibMotor::on(uint8_t index)
{
    switch (index)
    {
        case 0:
            digitalWrite(MOTOR_0, HIGH);
            break;
        case 1:
            digitalWrite(MOTOR_1, HIGH);
            break;
        case 2:
            digitalWrite(MOTOR_2, HIGH);
            break;
        case 3:
            digitalWrite(MOTOR_3, HIGH);
            break;
        case 4:
            digitalWrite(MOTOR_4, HIGH);
            break;
        default:
            break;
    }
}