#include "vex.h"
#include "robot-config.h"

using namespace vex;

brain Brain;
<<<<<<< HEAD
controller Controller1(primary);
controller Controller2(partner);

=======
controller Controller1;
>>>>>>> e97d08873244054079ed49d058478bd59efafe3c
motor LeftMotorA(PORT1, ratio6_1, true);
motor LeftMotorB(PORT18, ratio6_1, true);
motor LeftMotorC(PORT17, ratio6_1);
motor RightMotorA(PORT2, ratio6_1);
motor RightMotorB(PORT21, ratio6_1);
motor RightMotorC(PORT19, ratio6_1, true);
motor_group LeftMotors(LeftMotorA, LeftMotorB, LeftMotorC);
motor_group RightMotors(RightMotorA, RightMotorB, RightMotorC);
motor_group LeftRightMotors(LeftMotorA, LeftMotorB, LeftMotorC, RightMotorA, RightMotorB, RightMotorC);
motor IntakeMotor(PORT10, ratio18_1, false);

inertial InertialSensor(PORT2); 

