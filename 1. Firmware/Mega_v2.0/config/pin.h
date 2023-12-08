#pragma once

// #define LED 13

/*** Steppers ***/
#define X_STEP_PIN   54
#define X_DIR_PIN    55
#define X_ENABLE_PIN 38

#define Y_STEP_PIN   60
#define Y_DIR_PIN    61
#define Y_ENABLE_PIN 56

#define Z_STEP_PIN   46
#define Z_DIR_PIN    48
#define Z_ENABLE_PIN 62

#define E0_STEP_PIN   26
#define E0_DIR_PIN    28
#define E0_ENABLE_PIN 24

#define E1_STEP_PIN   36
#define E1_DIR_PIN    34
#define E1_ENABLE_PIN 30

// #define Z_CS_PIN  40
// #define E0_CS_PIN 42
// #define E1_CS_PIN 44

/*** Limit Switches ***/
#define X_MIN_PIN 3
// #define X_MAX_PIN 2
#define Y_MIN_PIN 14
// #define Y_MAX_PIN 15
#define Z_MIN_PIN 18

#define CAMERA_ZOOM_LIMIT  2
#define CAMERA_FOCUS_LIMIT 15

#define FLIP_LIMIT_PIN 19

/*** Relay pin ***/
#define POWER_PIN 49
/*** Lure Device ***/
#define FAN_PIN             53
#define MOSQUITO_KILLER_PIN 40
/*** Vibration Motor Pin ***/
#define MOTOR_0 23
#define MOTOR_1 50
#define MOTOR_2 52
#define MOTOR_3 35
#define MOTOR_4 37
/*** Light ***/
#define GLOB_LIGHT_PIN  27
#define LOCAL_LIGHT_PIN 29
/***********************/

/*** Servos ***/
#define SERVO_PIN 6
