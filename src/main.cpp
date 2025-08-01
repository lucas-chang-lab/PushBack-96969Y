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
#include "auton/auton.h"

using namespace vex;

competition Competition;
 
void autonomous() {
    timer benchmarkTimer;

}

void drivercontrol() {

}

int main() {

    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    //Brain.Screen.printAt( 10, 50, "Hello V6" );
    
    while(1) {
        //Motor1.spin(forward, 50, percent);
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
