#ifndef LINE_FOLLOWING_ROBOT_SERVO_MG995_MG995_H
#define LINE_FOLLOWING_ROBOT_SERVO_MG995_MG995_H

#include <stdint.h>

void mg995_set_angle(uint8_t angle);
void mg995_open_claw(void);
void mg995_close_claw(void);
void mg995_open_claw_delay(uint8_t p_angle, uint32_t delay);
void mg995_close_claw_delay(uint8_t p_angle, uint32_t delay);

#endif // LINE_FOLLOWING_ROBOT_SERVO_MG995_MG995_H
