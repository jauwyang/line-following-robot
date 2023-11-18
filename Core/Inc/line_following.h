#ifndef LINE_FOLLOWING_H
#define LINE_FOLLOWING_H

#include "tb6612fng/tb6612fng.h"

double getPathLinePosition(void);
double PIDAlgorithm(double currentLinePosition);
double convertRPM2PWM(double rpm);
void followLine(motor_t *leftMotor, motor_t *rightMotor);

#endif //LINE_FOLLOWING_H

