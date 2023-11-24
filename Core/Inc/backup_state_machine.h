 #ifndef BACKUP_STATE_MACHINE_H
 #define BACKUP_STATE_MACHINE_H

 #include "tb6612fng/tb6612fng.h"

 enum RobotSequence {
     START_B,
     FOLLOW_LINE_TO_TARGET_B,
     PICKUP_B,
     BACKUP_FROM_TARGET_B,
 	 ROTATE_TO_PATH_B,
     DRIVE_BACK_TO_LINE_B,
     FOLLOW_LINE_TO_START_B,
     END_B,
 };

 void start_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void followLine_ToTarget_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void pickup_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void backupFromTarget_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void rotateToPath_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void driveBackToLine_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void followLineToStart_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void end_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);
 void stateMachine_b(enum RobotSequence *currentState, motor_t *motorLeft, motor_t *motorRight);

 #endif // STATE_MACHINE_H
