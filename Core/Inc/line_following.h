#ifndef LINE_FOLLOWING_H
#define LINE_FOLLOWING_H

static const double CENTER_SENSOR = 0;
static const double GOAL = CENTER_SENSOR;

double PIDAlgorithm(double linePosition);
double getPathLinePosition();
void follow_line();

#endif //LINE_FOLLOWING_H

