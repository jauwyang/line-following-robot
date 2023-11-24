#include "state_machine.h"
#include "colour_sensor.h"
#include "line_following.h"

#include "mg995/mg995.h"
#include "motors.h"

#include <stdio.h>

void start(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {
	// transition state condition (switch automatically, START only used as entry point)
	*currentState = FOLLOW_LINE_TO_TARGET;

	//	uint16_t motorPWM = 1; // TODO: Change later (not max?)
//	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM, motorPWM);
//
//	// transition state condition (starting line detected)
//	uint32_t requiredSensorColourMatches = 4;
//	if (countMatchingSensorColourDetections(RED) >= requiredSensorColourMatches){
//		*currentState = FOLLOW_LINE_TO_TARGET;
//	}
}

void followLineToTarget(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Target detected and lined up to center
	if (countMatchingSensorColourDetections(BLUE) > 0){
		tb6612fng_stop(motorLeft, motorRight);
//		HAL_Delay(700);
		*currentState = PICKUP;
		return;
	}

	followLine(motorLeft, motorRight);
}

void pickup(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
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
	*currentState = BACKUP_FROM_TARGET;
}

void backupFromTarget(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	uint16_t motorPWM = 200;
	tb6612fng_move_rev(motorLeft, motorRight, motorPWM, motorPWM);
	HAL_Delay(1400);

	tb6612fng_stop(motorLeft, motorRight);
	// transition state condition (assume it has finished backing up)
	*currentState = ROTATE_TO_SAFE_ZONE;
}

void rotateToSafeZone(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Rotate 90 degrees CCW
	tb6612fng_move_rev_single(motorRight, 200);
	tb6612fng_move_fwd_single(motorLeft, 200);
	HAL_Delay(750);
	tb6612fng_stop(motorLeft, motorRight);

	*currentState = OFF_TRACK_TO_SAFE_ZONE_DRIVE;
}

void offTrackToSafeZoneDrive(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	uint16_t motorPWM = 250;
	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM , motorPWM);
//	HAL_Delay(1550);
//	tb6612fng_stop(motorLeft, motorRight);


	uint8_t middleSensorPosition = (ceil(SENSOR_COUNT / 2));

	// transition state condition (it reached the safe zone & is line up at robot's center)
	if (getPositionOfColourSource(GREEN) == middleSensorPosition){
		*currentState = DROPOFF;
	}
}

void dropOff(enum RobotSequence *currentState){
	// TODO: move robot set amount towards/away zone if needed
	mg995_open_claw();

	// transition state condition (assume it has dropped)
	*currentState = BACKUP_FROM_SAFE_ZONE;
}

void backUpFromSafeZone(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	uint16_t motorPWM = 200;
	tb6612fng_move_rev(motorLeft, motorRight, motorPWM - 22, motorPWM);
	HAL_Delay(3500);
	tb6612fng_stop(motorLeft, motorRight);

	*currentState = ROTATE_TO_TRACK;
}

void rotateToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {
	// Rotate 180 degrees CW
	uint16_t motorPWM = 200;
	tb6612fng_move_fwd_single(motorLeft, motorPWM);
	tb6612fng_move_rev_single(motorRight, motorPWM);
	HAL_Delay(900);
//	tb6612fng_stop(motorLeft, motorRight);

	*currentState = DRIVE_TO_TRACK;
}

void driveToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {
	uint16_t motorPWM = 250;
	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM, motorPWM);
	HAL_Delay(100);

	// Drive forward until middle sensor detects red line
	if (countMatchingSensorColourDetections(RED) > 0) {
		*currentState = FOLLOW_LINE_TO_START;
	}
}

void followLineToStart(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	followLine(motorLeft, motorRight);
	
	// Start/end line is detected
	uint8_t requiredSensorColourMatches = 3;
	if (countMatchingSensorColourDetections(RED) >= requiredSensorColourMatches) {
		*currentState = END;
	}
}

void end(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	// Stop the motors
	tb6612fng_stop(motorLeft, motorRight);
}

void stateMachine(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
    switch(*currentState){
        case START:
            start(currentState, motorLeft, motorRight);
            break;

        case PICKUP:
        	pickup(currentState, motorLeft, motorRight);
            break;

        case FOLLOW_LINE_TO_TARGET:
        	followLineToTarget(currentState, motorLeft, motorRight);
            break;

        case BACKUP_FROM_TARGET:
        	backupFromTarget(currentState, motorLeft, motorRight);
            break;

        case ROTATE_TO_SAFE_ZONE:
        	rotateToSafeZone(currentState, motorLeft, motorRight);
            break;

        case OFF_TRACK_TO_SAFE_ZONE_DRIVE:
        	offTrackToSafeZoneDrive(currentState, motorLeft, motorRight);
            break;

        case DROPOFF:
        	dropOff(currentState);
            break;

        case BACKUP_FROM_SAFE_ZONE:
        	backUpFromSafeZone(currentState, motorLeft, motorRight);
            break;

        case ROTATE_TO_TRACK:
        	rotateToTrack(currentState, motorLeft, motorRight);
        	break;

        case DRIVE_TO_TRACK:
        	driveToTrack(currentState, motorLeft, motorRight);
        	break;

        case FOLLOW_LINE_TO_START:
        	followLineToStart(currentState, motorLeft, motorRight);
            break;

        case END:
        	end(currentState, motorLeft, motorRight);
            break;

        default:
            printf("STATE MACHINE ERROR: UNKNOWN CASE\n");
			break;
    }
}
