#pragma once
#include "vex.h"
using namespace vex;

extern brain Brain;
extern controller Controller1;
extern controller Controller2;

extern motor LeftMotorA;
extern motor LeftMotorB;
extern motor LeftMotorC;
extern motor RightMotorA;
extern motor RightMotorB;
extern motor RightMotorC;
extern motor_group LeftMotors;
extern motor_group RightMotors;
extern motor_group LeftRightMotors;

extern motor intakeMotor;
extern motor intakeMotor2;
extern pneumatics botArmPneumatics;
extern pneumatics matchLoader;
extern pneumatics doubleParkPneumatic;

extern optical opticalSensor;
//extern optical opticalSensor2;

extern rotation LookRotation;
extern rotation RightRotation;

extern triport Expander1;

extern inertial InertialSensor;



