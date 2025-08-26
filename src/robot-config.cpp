#include "vex.h"
#include "robot-config.h"

using namespace vex;

brain Brain;
controller Controller1(primary);
controller Controller2(partner);

motor LeftMotorA(PORT1, ratio6_1, true);
motor LeftMotorB(PORT2, ratio6_1, true);
motor LeftMotorC(PORT3, ratio6_1, true);
motor RightMotorA(PORT8, ratio6_1);
motor RightMotorB(PORT9, ratio6_1);
motor RightMotorC(PORT10, ratio6_1);
motor_group LeftMotors(LeftMotorA, LeftMotorB, LeftMotorC);
motor_group RightMotors(RightMotorA, RightMotorB, RightMotorC);
motor_group LeftRightMotors(LeftMotorA, LeftMotorB, LeftMotorC, RightMotorA, RightMotorB, RightMotorC);
motor intakeMotor(PORT4, ratio18_1, false);


inertial InertialSensor(PORT2); 

