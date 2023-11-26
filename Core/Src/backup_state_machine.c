 #include "BACKUP_state_machine.h"
 #include "colour_sensor.h"
 #include "line_following.h"

 #include "mg995/mg995.h"
 #include "motors.h"

 #include <stdio.h>

 void start_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {
 	// transition state condition (switch automatically, START only used as entry point)
 	*currentState = FOLLOW_LINE_TO_TARGET_B;
 }

 void followLineToTarget_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	followLine(motorLeft, motorRight);
 	// Target detected and lined up to center
 	if (countMatchingSensorColourDetections(BLUE) > 0){
 		tb6612fng_stop(motorLeft, motorRight);
 		HAL_Delay(2000);
 		*currentState = PICKUP_B;
 	}
 }

 void pickup_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	// Drive forward at full speed
     tb6612fng_move_fwd(motorLeft, motorRight, MAX_PWM, MAX_PWM);
     HAL_Delay(2500);

     // // transition state condition (assumed it has picked up)
 	*currentState = BACKUP_FROM_TARGET_B;
 }

 void backupFromTarget_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	uint16_t motorPWM = 200;
 	tb6612fng_move_rev(motorLeft, motorRight, motorPWM, motorPWM);
 	HAL_Delay(2500);

 	// transition state condition (assume it has finished backing up)
 	*currentState = ROTATE_TO_PATH_B;
 }
 
 void rotateToPath_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	// Rotate 180 degrees CCW
 	tb6612fng_move_fwd_single(motorRight, 200);
 	tb6612fng_move_rev_single(motorLeft, 200);
 	HAL_Delay(2*1750);

 	*currentState = DRIVE_BACK_TO_LINE_B;
 }

 void driveBackToLine_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	uint16_t motorPWM = 250;
 	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM, motorPWM);

 	uint8_t middleSensorPosition = (ceil(SENSOR_COUNT / 2));

 	// transition state condition (it reached the safe zone & is line up at robot's center)
 	if (getPositionOfColourSource(RED) == middleSensorPosition){
 		*currentState = FOLLOW_LINE_TO_START_B;
 	}
 }

 void followLineToStart_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	followLine(motorLeft, motorRight);
	
 	// Start/end line is detected
 	uint8_t requiredSensorColourMatches = 3;
 	if (countMatchingSensorColourDetections(RED) >= requiredSensorColourMatches) {
 		*currentState = END_B;
 	}
 }

 void end_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
 	// Stop the motors
 	tb6612fng_stop(motorLeft, motorRight);
 }

 void stateMachine_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
     switch(*currentState){
         case START_B:
             start_b(currentState, motorLeft, motorRight);
             break;

         case FOLLOW_LINE_TO_TARGET_B:
         	followLineToTarget_b(currentState, motorLeft, motorRight);
             break;

         case PICKUP_B:
         	pickup_b(currentState, motorLeft, motorRight);
             break;

         case BACKUP_FROM_TARGET_B:
         	backupFromTarget_b(currentState, motorLeft, motorRight);
             break;

         case ROTATE_TO_PATH_B:
             rotateToPath_b(currentState, motorLeft, motorRight);
             break;

         case DRIVE_BACK_TO_LINE_B:
             driveBackToLine_b(currentState, motorLeft, motorRight);
             break;

         case FOLLOW_LINE_TO_START_B:
         	followLineToStart_b(currentState, motorLeft, motorRight);
             break;

         case END_B:
         	end_b(currentState, motorLeft, motorRight);
             break;

         default:
             printf("STATE MACHINE ERROR: UNKNOWN CASE\n");
 			break;
     }
 }
