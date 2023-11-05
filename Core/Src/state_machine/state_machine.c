#include "state_machine.h"
#include "colour_sensor.h"
#include <stdio.h>


// find out if a colour has been detected (set number of them has been detected)
// follow line (location of estimated line source)
// create


void start(){
	//uint32_t rawSensorReadings[] = [INSERT RAW SENSOR READING FUNCTION HERE];
	bool processedSensorReadings[] = processColourSensorReadings(rawSensorReadings, SENSOR_COUNT, RED);
	// how do we start lol
}

void followLineToTarget(enum RobotSequence *currentState){
	followLine();
	if (getPositionOfColourSource(SENSOR_COUNT, BLUE) == CENTER_SENSOR){
		&currentState = PICKUP;
	}
}


void pickup(enum RobotSequence *currentState){
	// move up set amount towards character if needed
	mg995_close_claw();
	// may need to wait XX amount of time such that robot has enough time to grab lego before entering next state
	&currentState = BACKUP_FROM_TARGET;
}


void backupFromTarget(enum RobotSequence *currentState){
	//reverse backwards
	&currentState = ROTATE_TO_SAFEZONE;
}

void rotateToSafezone(enum RobotSequence *currentState){
	//run command to rotate motor X amount
	&currentState = OFF_TRACK_TO_SAFEZONE_DRIVE;
}


void offTrackToSafezoneDrive(enum RobotSequence *currentState){
	//drive forward
	if (getPositionOfColourSource(SENSOR_COUNT, GREEN) == CENTER_SENSOR){
		&currentState = DROPOFF;
	}
}


void dropOff(enum RobotSequence *currentState){
	mg995_open_claw();
	&currentState = BACKUP_FROM_SAFEZONE;
}


void backUpFromSafezone(enum RobotSequence *currentState){
	//reverse backwards
	&currentState = RETURN_TO_TRACK;
}

void returnToTrack(enum RobotSequence *currentState){
	if ()
	&currentState =
}


void followLineToStart(enum RobotSequence *currentState){
	followLine();

}


void end(enum RobotSequence *currentState){
	//stop the motor
	//change state to start or no need?
}


void stateMachine(enum RobotSequence *currentState){
    switch(currentState){
        case START:
            start(currentState);
            break;

        case FOLLOW_LINE_TO_TARGET:
        	followLineToTarget(currentState);
            break;

        case PICKUP:
        	pickup(currentState);
            break;

        case BACKUP_FROM_TARGET:
        	backupFromTarget(currentState);
            break;

        case ROTATE_TO_SAFEZONE:
        	rotateToSafezone(currentState);
            break;

        case OFF_TRACK_TO_SAFEZONE_DRIVE:
        	offTrackToSafezoneDrive(currentState);
            break;

        case DROPOFF:
        	dropOff(currentState);
            break;

        case BACKUP_FROM_SAFEZONE:
        	backUpFromSafezone(currentState);
            break;

        case RETURN_TO_TRACK:
        	returnToTrack(currentState);
            break;

        case FOLLOW_LINE_TO_START:
        	followLineToStart(currentState);
            break;

        case END:
        	end(currentState);
            break;

        default:
            printf("STATE MACHINE ERROR: UNKNOWN CASE\n");
    }
}
