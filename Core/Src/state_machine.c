#include "state_machine.h"
#include "colour_sensor.h"
#include "line_following.h"

#include "mg995/mg995.h"

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
	followLine(motorLeft, motorRight);

	uint8_t middleSensorPosition = (floor(SENSOR_COUNT / 2.0));

	// transition state condition (target detected & is lined up to its center)
	if (getPositionOfColourSource(BLUE) == middleSensorPosition){
		*currentState = PICKUP;
	}
}

void pickup(enum RobotSequence *currentState){
	// TODO: move up set amount towards character if needed
	mg995_close_claw();
	
	// transition state condition (assumed it has picked up)
	*currentState = BACKUP_FROM_TARGET;
}

void backupFromTarget(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	uint16_t motorPWM = 1;	// TODO: Change later
	tb6612fng_move_rev(motorLeft, motorRight, motorPWM, motorPWM);
	
	// transition state condition (assume it has finished backing up)
	*currentState = ROTATE_TO_SAFE_ZONE;
}

void rotateToSafeZone(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	//run command to rotate motor X amount

	// Rotate 90 degrees CCW
	//tb6612fng_rotate(motorLeft, motorRight, rotation_params);

	// transition state condition (assumed it has rotated)
	*currentState = OFF_TRACK_TO_SAFE_ZONE_DRIVE;
}

void offTrackToSafeZoneDrive(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	//drive forward
	uint16_t motorPWM = 1;	// TODO: Change later
	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM, motorPWM);

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
	//reverse backwards
	uint16_t motorPWM = 1;	// TODO: Change later
	tb6612fng_move_rev(motorLeft, motorRight, motorPWM, motorPWM);

	// transition state condition (assume it has backed up)
	*currentState = ROTATE_TO_TRACK;
}

void rotateToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {

	// Rotate 180 degrees CCW
	//tb6612fng_rotate(motorLeft, motorRight, rotation_params);
	*currentState = DRIVE_TO_TRACK;
}

void driveToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight) {
	uint16_t motorPWM = 0;	// TODO: Change later
	tb6612fng_move_fwd(motorLeft, motorRight, motorPWM, motorPWM);

	uint8_t middleSensorPosition = (ceil(SENSOR_COUNT / 2));

	// transition state condition (it detects the path again)
	// Drive forward until middle sensor detects red line
	if (getPositionOfColourSource(RED) == middleSensorPosition) {
		*currentState = FOLLOW_LINE_TO_START;
	}
}

void followLineToStart(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight){
	followLine(motorLeft, motorRight);
	
	// transition state condition (start/end line detected)
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

        case FOLLOW_LINE_TO_TARGET:
        	followLineToTarget(currentState, motorLeft, motorRight);
            break;

        case PICKUP:
        	pickup(currentState);
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
