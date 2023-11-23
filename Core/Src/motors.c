// #include "motors.h"
// #include "tb6612fng/tb6612fng.h"

// /**
//  * Motor Characterization 
//  */

// /**
//  * Physical Constants
// */

// #define WHEEL_CIRCUMFERENCE (double) 22.3 //cm

// static const uint16_t linearDistanceFactor = 1;
// static const uint16_t angularRotationFactor = 1;

// static const dataPointsCount = 1;

// typedef struct {
//     double distance; //cm
//     double time; //idk units lol
// } DataPoint;

// DataPoint experimentPoints[] = {
//     {
//         .distance = 1;
//         .time = 1;
//     },
//     {
//         .distance = 1;
//         .time = 1;
//     },
//     {
//         .distance = 1;
//         .time = 1;
//     },
//     {
//         .distance = 1;
//         .time = 1;
//     },
// }


// static uint16_t computeTimeFactor(const uint16_t targetDistance) {
//     // Checks if point exists
//     bool exists = false;
//     uint16_t mid;

//     uint16_t left = 0;
//     uint16_t right = dataPointsCount - 1;

//     // checks if the distance has already been recorded
//     while (left <= right) {
//         mid = left + (right - left) / 2;
//         if (experimentPoints[mid].distance == targetDistance) {
//             exists = true;
//             break;
//         } else if (experimentPoints[mid].distance < targetDistance) {
//             left = mid + 1;
//         } else {
//             right = mid - 1;
//         }
//     }

//     // interpolates if the value is in between
//     if (exists == true) {
//         return experimentPoints[mid].time;
//     } else {
//         if (mid == 0) { mid++; }
//         double interpolated_distance = experimentPoints[mid - 1].distance + (experimentPoints[mid].time - experimentPoints[mid - 1].time) * ((experimentPoints[mid].distance - experimentPoints[mid - 1].distance) / (experimentPoints[mid].time - experimentPoints[mid - 1].time));

//         return interpolated_distance;
//     }
// }

// void travelSetDistance(motor_t *motor_left, motor_t *motor_right, const LinearParams params) {
//     uint16_t pwm = params.distance*movementFactor;

    

//     if (params.direction == DIR_FORWARD) {
//         tb6612fng_move_fwd(motorLeft, motorRight, pwm);
//     } else {
//         tb6612fng_rev_fwd(motorLeft, motorRight, pwm);        
//     }
// }

// /**
//  * Rotate the robot on the spot. PWM characterization results:
//  * 90 degrees, CW:  
//  * 90 degrees, CCW: 
//  * 180 degrees, CW: 
//  * 180 degrees, CCW: 
//  * 270 degrees, CW: 
//  * 270 degrees CCW: 
//  * 
// */
// void rotateRobotCenter(motor_t *motorLeft, motor_t *motorRight, const RotationParams params) {
//     // Apply linear interpolation algorithm to obtain angle values
    
    
//     if (params.direction == DIR_CW) {
        

//     } else {

//     }
// }
