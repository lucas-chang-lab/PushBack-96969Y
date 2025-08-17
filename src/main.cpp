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
#include "auton/auton.h"

using namespace vex;

competition Competition;
timer drivingTimer;

void pre_auton() {
    controls::startThreads();
    controls::preauton();
    

    auton::showAutonRunType();
}

void autonomous() {
    timer benchmarkTimer;

    auton::runAutonomous();
}

void userRunAutonomous() {
    task::sleep(1500);
    
    autonomous();
}

void usercontrol() {
    drivingTimer.reset();

    if (auton::isUserRunningAuton()) {
        userRunAutonomous();
    }

    controls::setUpKeybinds();
    
    controls::resetStates();

    while(1) {
        controls::doControls();

        wait(20, msec);
    }
}

int main() {

    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    //Brain.Screen.printAt( 10, 50, "Hello V6" );
    pre_auton();

    while(1) {
        wait(100, msec);
    }
}
