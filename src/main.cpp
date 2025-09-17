/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       lucaschang                                                */
/*    Created:      7/16/2025, 3:30:02 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robot-config.h"
#include "controls.h"
#include "Auton/auton.h"
#include "Auton/preauton.h"


using namespace vex;

competition Competition;
timer drivingTimer;

void pre_auton() {
    InertialSensor.calibrate();
    preauton::waitCalibrating();
    //controls::startThreads();
    //controls::preauton();

    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 50, "pre_auton done");
}

void autonomous() {
    timer benchmarkTimer;

    auton::runAutonomous();
}

void usercontrol() {
    drivingTimer.reset();

    if (auton::isUserRunningAuton()) {
        autonomous();
    }

    controls::setUpKeybinds();
    controls::resetStates();

    while(1) {
        controls::doControls();

        //printf("Heading: %.2f \n", InertialSensor.heading());
        //printf("Rotation: %.2f \n", InertialSensor.rotation());
        wait(20, msec);
    }
}

int main() {
    pre_auton();
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    while(1) {
        wait(100, msec);
    }
}
