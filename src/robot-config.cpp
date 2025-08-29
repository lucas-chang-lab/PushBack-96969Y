#include "vex.h"
#include "robot-config.h"

using namespace vex;

brain Brain;
controller Controller1(primary);
controller Controller2(partner);

motor LeftMotorA(PORT4, ratio6_1, true);
motor LeftMotorB(PORT15, ratio6_1, true);
motor LeftMotorC(PORT16, ratio6_1, true);
motor RightMotorA(PORT1, ratio6_1);
motor RightMotorB(PORT2, ratio6_1);
motor RightMotorC(PORT3, ratio6_1);
motor_group LeftMotors(LeftMotorA, LeftMotorB, LeftMotorC);
motor_group RightMotors(RightMotorA, RightMotorB, RightMotorC);
motor_group LeftRightMotors(LeftMotorA, LeftMotorB, LeftMotorC, RightMotorA, RightMotorB, RightMotorC);

motor intakeMotor(PORT8, ratio18_1, false);
motor intakeMotor2(PORT9, ratio18_1, false);
motor intakeMotor3(PORT10, ratio18_1, false);

rotation LookRotation(PORT20);
rotation RightRotation(PORT19);

triport Expander1(PORT18);
encoder LookEncoder(Expander1.C);
inertial InertialSensor(PORT2); 

