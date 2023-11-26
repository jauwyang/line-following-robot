#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "tb6612fng/tb6612fng.h"

enum RobotSequence {
    START,
    FOLLOW_LINE_TO_TARGET,
    PICKUP,
    BACKUP_FROM_TARGET,
	ROTATE_TO_SAFE_ZONE,
    OFF_TRACK_TO_SAFE_ZONE_DRIVE,
    DROPOFF,
    BACKUP_FROM_SAFE_ZONE,
	ROTATE_TO_TRACK,
	DRIVE_TO_TRACK,
    FOLLOW_LINE_TO_START,
    END,
};

void start(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void followLineToTarget(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void pickup(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void backupFromTarget(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void rotateToSafeZone(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void offTrackToSafeZoneDrive(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void dropOff(enum RobotSequence *currentState);
void backUpFromSafeZone(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void rotateToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void driveToTrack(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void followLineToStart(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void end(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
void stateMachine(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);

#endif // STATE_MACHINE_H
