#ifndef STATE_MACHINE_START_H
#define STATE_MACHINE_START_H

#include "tb6612fng/tb6612fng.h"

enum RobotSequence_start {
    START_START,
    FOLLOW_LINE_TO_TARGET_START,
    PICKUP_START,
    BACKUP_FROM_TARGET_START,
	ROTATE_TO_LINE_START,
	DRIVE_TO_LINE_START,
    FOLLOW_LINE_TO_START_START,
    END_START,
};

void start_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void followLineToTarget_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void pickup_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void backupFromTarget_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void rotateToLine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void rotateToLine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void followLineToStart_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void end_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);
void stateMachine_start(enum RobotSequence_start *currentState, motor_t *motorLeft, motor_t *motorRight);

#endif // STATE_MACHINE_H
