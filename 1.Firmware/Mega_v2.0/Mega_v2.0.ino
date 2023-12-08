#include "setup.hpp"

void setup()
{
    Serial.begin(115200);
    Serial2.begin(9600);
    setPin();
    setStepper();

    gLureServo.attach(SERVO_PIN, 500, 2500);   // 修正脉冲宽度;
}

VibMotor gVibMotor;

void loop()
{
    float distance_x, distance_y;
    unsigned char vib_index;   // The index of which motor should be activated.
    Command command;
    /***
     Read the serial, check if it had any data.
     And Serial.availabel() returns the number
     of bytes of data in the serial port.
    **/

    if (Serial.available())
    {
        Serial.readBytes((char*)&command, sizeof(Command));
        Serial.readBytes((char*)&distance_x, sizeof(float));
        Serial.readBytes((char*)&distance_y, sizeof(float));
        vib_index = static_cast<unsigned char>(distance_x);
        if (static_cast<int>(distance_x) >= MAX_DISTANCE_X || static_cast<int>(distance_y) >= MAX_DISTANCE_Y)
        {
            // Serial.println("Out of range!");
            command = Command::OUT_RANGE;
        }
        // if (distance_x > MAX_DISTANCE_X || distance_y > MAX_DISTANCE_Y)
        // {
        //     // Serial.println("Out of range!");
        //     command = Command::OUT_RANGE;
        // }
        switch (command)
        {
            case Command::FAN_ON:
                LureDevice::fanOn();
                Serial.println("Task done");
                break;
            case Command::FAN_OFF:
                LureDevice::fanOff();
                Serial.println("Task done");
                break;
            case Command::MOSQUITO_KILLER_ON:
                LureDevice::mosquitokillerOn();
                Serial.println("Task done");
                break;
            case Command::MOSQUITO_KILLER_OFF:
                LureDevice::mosquitokillerOff();
                Serial.println("Task done");
                break;
            case Command::OUTLET_OPEN:
                LureDevice::outletOpen();
                Serial.println("Task done");
                break;
            case Command::OUTLET_CLOSE:
                LureDevice::outletClose();
                Serial.println("Task done");
                break;
            case Command::POWER_ON:
                powerOn();
                Serial.println("Task done");
                break;
            case Command::INIT:
                initDevice();
                Serial.println("Task done");
                break;
            case Command::VIB:
                gVibMotor.activate(vib_index);
                Serial.println("Task done");
                break;
            case Command::Z:
                gStepperZ.runToNewPosition(115 * z_steps_permm);
                Serial.println("Task done");
                break;
            case Command::FLIP:
                flipVibPlate();
                Serial.println("Task done");
                break;
            case Command::XY:
                moveXY(distance_x, distance_y);
                Serial.println("Task done");
                break;
            case Command::READY_CAMERA:
                readyCamera();
                Serial.println("Task done");
                break;
            case Command::POWER_OFF:
                powerOff();
                Serial.println("Task done");
                break;
            /*** For Camera ***/
            case Command::INIT_CAMERA:
                camera::init();
                Serial.println("Task done");
                break;
            case Command::GLOB_CAMERA:
                camera::global();
                Serial.println("Task done");
                break;
            case Command::LOCAL_CAMERA_1:
                camera::local_1();
                Serial.println("Task done");
                break;
            case Command::LOCAL_CAMERA_2:
                camera::local_2();
                Serial.println("Task done");
                break;
            case Command::LOCAL_CAMERA_3:
                camera::local_3();
                Serial.println("Task done");
                break;
            /********************/
            case Command::OUT_RANGE:
                Serial.println("X or Y is out of range!");
                break;
            default:
                Serial.println("Command format error!");
                break;
        }
    }
    delay(10);
}

// void loop()
// {
//     if (digitalRead(CAMERA_FOCUS_LIMIT) == HIGH)
//     {
//         LureDevice::fanOn();
//     }
//     else
//     {
//         LureDevice::fanOff();
//     }
//     // if (digitalRead(CAMERA_FOCUS_LIMIT == HIGH))
//     // {
//     //     LureDevice::mosquitokillerOn();
//     // }
//     // else
//     // {
//     //     LureDevice::mosquitokillerOff();
//     // }
// }