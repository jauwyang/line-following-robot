#ifndef LINE_FOLLOWING_ROBOT_IR_LINE_FOLLOWING_H
#define LINE_FOLLOWING_ROBOT_IR_LINE_FOLLOWING_H

#include <stdint.h>

double IR_getPathLinePosition(const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount);
double IR_PIDAlgorithm(double currentLinePosition);
void IR_followLine(motor_t *leftMotor, motor_t *rightMotor, const uint32_t IR_rawSensorReadings[], const uint8_t sensorCount);

#endif // LINE_FOLLOWING_ROBOT_IR_LINE_FOLLOWING_H
