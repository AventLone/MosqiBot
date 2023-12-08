#pragma once

/*** Params ***/
#define MAX_DISTANCE_X (206 - 22.1 * 2)                   // The maximum distance of the x axis (mm)
#define MAX_DISTANCE_Y 183                                // The maximum distance of the y axis (mm)

#define MM_PER_CIRCLE_X 40                                // The x distance of per circle (mm)
#define MM_PER_CIRCLE_Y 40                                // The y distance of per circle (mm)
#define MM_PER_CIRCLE_Z 8.5                               // The z distance of per circle (mm)

#define CIRCLE_STEPS (200 * 16)                           // Step angle is 1.8 degrees, and subdivision mode is 1/16

#define STEPS_PER_MM_X (CIRCLE_STEPS / MM_PER_CIRCLE_X)   // The number of steps per mm on x
#define STEPS_PER_MM_Y (CIRCLE_STEPS / MM_PER_CIRCLE_Y)   // The number of steps per mm on y
#define STEPS_PER_MM_Z CIRCLE_STEPS / MM_PER_CIRCLE_Z     // The number of steps per mm on z

/*** Target position of Z stepper ***/
const long z_steps_permm = 10000.0f / 24.73f;
// const long z_target[3] = {120, 36, 0};