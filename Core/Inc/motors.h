 #ifndef LINE_FOLLOWING_ROBOT_MOTORS_H
 #define LINE_FOLLOWING_ROBOT_MOTORS_H

 /**
  * @file motors.h
  * @brief High-level motor control API for travelling a set distance and rotating the robot.
  * 	High-level functionality is based on an interpolation algorithm using BST.
  */

#include "tb6612fng/tb6612fng.h"
 #include <stdint.h>

/**
 * Constants
 */
#define LINEAR_PWM				(uint16_t) 200
#define ROTATION_PWM			(uint16_t) 200
#define WHEEL_CIRCUMFERENCE_CM	(double) 22.3


typedef enum _LinearDirection {

    DIR_FORWARD = 0,    // Forward
    DIR_REVERSE         // Reverse

 } LinearDirection;

typedef enum _RotationalDirection {

    DIR_CW = 0, // Clockwise
    DIR_CCW     // Counter-Clockwise

} RotationalDirection;

 /**
  * Structure containing parameters for linear travel
  * @field distance - Desired distance to travel in cm
  * @field direction - Forward or reverse
  */
typedef struct _LinearParams {

    uint16_t distanceCm;
    LinearDirection direction;

} LinearParams;

/**
 * Structure containing parameters for rotation
 * @field angle - Degrees of rotation
 * @field direction - Clockwise or counter-clockwise
 */
typedef struct _RotationParam {

    uint16_t angle;
    RotationalDirection direction;

} RotationParams;

/**
 * Characterization unit representing a single data point.
 * Note that displacement can be used for both linear and angular purposes
 */
typedef struct _DataPoint {

    double displacement;
    double timeSec;

} DataPoint;

/**
 * User-facing API
 */
void travelSetDistance(motor_t *motorLeft, motor_t *motorRight, LinearParams params);
void rotateRobot(motor_t *motorLeft, motor_t *motorRight, RotationParams params);

 #endif // LINE_FOLLOWING_ROBOT_MOTORS_H
