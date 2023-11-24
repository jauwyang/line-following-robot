#include "state_machine_start.h"
#include "colour_sensor.h"
#include "line_following.h"

#include "mg995/mg995.h"
#include "motors.h"

#include <stdio.h>

void start_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight) {
	// transition state condition (switch automatically, START only used as entry point)
	*currentState = FOLLOW_LINE_TO_TARGET_START;
}

void followLineToTarget_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Target detected and lined up to center
	if (countMatchingSensorColourDetections(BLUE) > 0){
		tb6612fng_stop(motorLeft, motorRight);
	//		HAL_Delay(700);
		*currentState = PICKUP_START;
		return;
	}

	followLine(motorLeft, motorRight);
}

void pickup_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
//	mg995_open_claw();
//	HAL_Delay(1000);
//
//	mg995_close_claw();

	// Reverse to space from target
	HAL_Delay(500);
	tb6612fng_move_rev(motorLeft, motorRight, 200 - 22, 200);
	HAL_Delay(400);
	tb6612fng_stop(motorLeft, motorRight);
	HAL_Delay(500);
	mg995_open_claw();

	// Rotate clockwise to aim the target
	tb6612fng_move_rev_single(motorLeft, 75);
	tb6612fng_move_fwd_single(motorRight, 75);
	HAL_Delay(290);
//	tb6612fng_stop(motorLeft, motorRight);

	// Open claw
//	mg995_open_claw();
//	HAL_Delay(1000);
//
	// Drive toward target
	tb6612fng_move_fwd(motorLeft, motorRight, 200 - 22, 200);
	HAL_Delay(500);

	// Close the claw
	mg995_close_claw();

	// transition state condition (assumed it has picked up)
	*currentState = BACKUP_FROM_TARGET_START;
}

void backupFromTarget_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	uint16_t motorPWM = 200;
	tb6612fng_move_rev(motorLeft, motorRight, motorPWM, motorPWM);
	HAL_Delay(1700);

	tb6612fng_stop(motorLeft, motorRight);
	// transition state condition (assume it has finished backing up)
	*currentState = ROTATE_TO_LINE_START;
}

void rotateToLine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Rotate 90 degrees CCW
	tb6612fng_move_rev_single(motorLeft, 200);
	tb6612fng_move_fwd_single(motorRight, 200);
	HAL_Delay(750);
	tb6612fng_stop(motorLeft, motorRight);

	*currentState = DRIVE_TO_LINE_START;

}

void driveToLine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight) {
	tb6612fng_move_rev(motorLeft, motorRight, 200, 200);

	if (countMatchingSensorColourDetections(RED) > 0){
		tb6612fng_stop(motorLeft, motorRight);
	//		HAL_Delay(700);
		*currentState = FOLLOW_LINE_TO_START_START;
	}
}

void followLineToStart_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	followLine(motorLeft, motorRight);

	// Start/end line is detected
	uint8_t requiredSensorColourMatches = 3;
	if (countMatchingSensorColourDetections(RED) >= requiredSensorColourMatches) {
		*currentState = END_START;
	}
}

void end_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Stop the motors
	tb6612fng_stop(motorLeft, motorRight);
}

void stateMachine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight){
	switch(*currentState){
	 case START_START:
		 start_start(currentState, motorLeft, motorRight);
		 break;

	 case FOLLOW_LINE_TO_TARGET_START:
		 followLineToTarget_start(currentState, motorLeft, motorRight);
		 break;

	 case PICKUP_START:
		 pickup_start(currentState, motorLeft, motorRight);
		 break;

	 case BACKUP_FROM_TARGET_START:
		 backupFromTarget_start(currentState, motorLeft, motorRight);
		 break;

	 case ROTATE_TO_LINE_START:
		 rotateToLine_start(currentState, motorLeft, motorRight);
		 break;

	 case FOLLOW_LINE_TO_START_START:
		 followLineToStart_start(currentState, motorLeft, motorRight);
		 break;

	 case END_START:
		 end_start(currentState, motorLeft, motorRight);
		 break;

	 default:
		 printf("STATE MACHINE ERROR: UNKNOWN CASE\n");
		break;
	}
}
