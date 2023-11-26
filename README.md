# line-following-robot

Search and rescue robot able to autonomously navigate a course by following a line, detecting and picking up an object, and placing said object in a space-constrained region

## Key Features
* Implements a PID controller for steering; uses colour sensor feedback to control speed and direction of DC motors via timer-controlled PWM
* Slow-decay, dual H-Bridge DC motor control for rapid rotor stop via current recirculation / back EMF
* DC motor operation at sufficiently low PWM frequencies for a lower spin threshold and a wider linear operating region   
* I2C fast mode for high frequency sampling of terrain to complete objectives
* Servo-driven gripper mechanism for high-precision position control
