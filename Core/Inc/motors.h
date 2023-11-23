// #ifndef LINE_FOLLOWING_ROBOT_MOTORS_H
// #define LINE_FOLLOWING_ROBOT_MOTORS_H

// /**
//  * @file motors.h
//  * @brief High-level motor control API for travelling a set distance and rotating the robot 
//  */

// #include <stdint.h>

// typedef enum _LinearDirection {

//     DIR_FORWARD = 0,    // Forward
//     DIR_REVERSE         // Reverse

// } LinearDirection;

// typedef enum _RotationalDirection {

//     DIR_CW = 0, // Clockwise
//     DIR_CCW     // Counter-Clockwise

// } RotationalDirection;

// typedef struct _LinearParams {

//     uint16_t distance;
//     LinearDirection direction;

// } LinearParams;

// typedef struct _RotationParam {

//     uint16_t angle;
//     RotationalDirection direction;

// } RotationParams;

// void travelSetDistance(motor_t *motor_left, motor_t *motor_right, LinearParams params);
// void rotateRobotCenter(motor_t *motor_left, motor_t *motor_right, RotationParams params);

// #endif // LINE_FOLLOWING_ROBOT_MOTORS_H
