#include "vex.h"
#include "robot-config.h"

using namespace vex;

brain Brain;
controller Controller1(primary);
controller Controller2(partner);

motor LeftMotorA(PORT8, ratio6_1, false);
motor LeftMotorB(PORT9, ratio6_1, true);
motor LeftMotorC(PORT20, ratio6_1, false);
motor RightMotorA(PORT1, ratio6_1, true);
motor RightMotorB(PORT2, ratio6_1, false);
motor RightMotorC(PORT11, ratio6_1, true);
motor_group LeftMotors(LeftMotorA, LeftMotorB, LeftMotorC);
motor_group RightMotors(RightMotorA, RightMotorB, RightMotorC);
motor_group LeftRightMotors(LeftMotorA, LeftMotorB, LeftMotorC, RightMotorA, RightMotorB, RightMotorC);

motor intakeMotor(PORT17, ratio18_1, false);
motor intakeMotor2(PORT18, ratio18_1, false);


pneumatics botArmPneumatics(Brain.ThreeWirePort.A);
pneumatics trapDoorPneumatics(Brain.ThreeWirePort.B);

rotation LookRotation(PORT4);
rotation RightRotation(PORT5);

triport Expander1(PORT6);

inertial InertialSensor(PORT18); 

