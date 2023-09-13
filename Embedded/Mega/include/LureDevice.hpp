#include <Servo.h>
// Servo lure_servo;


// void on()
// {
//     for (int i = 0; i < 100; ++i)
//     {
//         digitalWrite(SERVO_PIN, HIGH);
//         vTaskDelay(1 / portTICK_PERIOD_MS);
//         digitalWrite(SERVO_PIN, LOW);
//         vTaskDelay(19 / portTICK_PERIOD_MS);
//     }
//     digitalWrite(FAN_PIN, HIGH);
// }

// void LureOff()
// {
//     digitalWrite(FAN_PIN, LOW);
//     for (int i = 0; i < 100; ++i)
//     {
//         digitalWrite(SERVO_PIN, HIGH);
//         vTaskDelay(2 / portTICK_PERIOD_MS);
//         digitalWrite(SERVO_PIN, LOW);
//         vTaskDelay(18 / portTICK_PERIOD_MS);
//     }
// }

class LureDevice
{
public:
    LureDevice()
    {
        // pinMode(SERVO_PIN, OUTPUT);
        pinMode(FAN_PIN, OUTPUT);
    }

    void on();
    void off();

private:
    Servo lure_servo;
};

void LureDevice::on()
{
    // for (int i = 0; i < 9999; ++i)
    // {
    //     digitalWrite(SERVO_PIN, HIGH);
    //     vTaskDelay(1 / portTICK_PERIOD_MS);
    //     digitalWrite(SERVO_PIN, LOW);
    //     vTaskDelay(19 / portTICK_PERIOD_MS);
    // }
    // lure_servo.atta
    lure_servo.attach(SERVO_PIN);
    if (lure_servo.read() != 0)
    {
        for (int pos = lure_servo.read(); pos >= 0; --pos)   // From 170° to 0°
        {
            lure_servo.write(pos);                           // 指定舵机转向的角度
            vTaskDelay(30 / portTICK_PERIOD_MS);
        }
    }
    lure_servo.detach();
    digitalWrite(FAN_PIN, HIGH);
}

void LureDevice::off()
{
    digitalWrite(FAN_PIN, LOW);
    lure_servo.attach(SERVO_PIN);
    for (int i = 0; i < 9999; ++i)
    {
        digitalWrite(SERVO_PIN, HIGH);
        vTaskDelay(2 / portTICK_PERIOD_MS);
        digitalWrite(SERVO_PIN, LOW);
        vTaskDelay(18 / portTICK_PERIOD_MS);
    }
    lure_servo.detach();
}
