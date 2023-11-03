#include "line_following.h"

static const double SENSOR_COUNT = 5;

// PID Gain Constants
static const double Kp = 1;
static const double Kd = 0;
static const double Ki = 0;

double previousError = 0;

double PID_calculator(double linePosition) {
	double error = GOAL - linePosition;

	double errorDerivative = error - previousError;
	double errorIntegral = errorIntegral + error;

	double steeringValue = Kp*error + Ki*errorIntegral + Kd*errorDerivative;

	previousError = error;

	return steeringValue;
	//TODO: SCALE THE VALUES SO THAT (I.E. HOW MUCH THE THING SHOULD TURN)
}
