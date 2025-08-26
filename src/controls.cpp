#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/botIntake.h"
#include "main.h"


namespace controls {
    void startThreads() {
        task intakeThread([]() -> int {
            botIntake::runThread();
            return 1;
        });
    }

    void setUpKeybinds() {
        Controller2.ButtonX.pressed([]() -> void {

        });
        Controller1.ButtonX.pressed([]() -> void {

        });
        Controller1.ButtonY.pressed([]() -> void {

        });
        Controller1.ButtonA.pressed([]() -> void {

        });
        Controller1.ButtonB.pressed([]() -> void {

        });
        Controller1.ButtonL2.pressed([]() -> void {

        });
        Controller1.ButtonL1.pressed([]() -> void {

        });
        Controller1.ButtonUp.pressed([]() -> void {

        });

    }

    void preauton() {
        botdrive::preauton();
        controls::startThreads();
    }


    void resetStates() {
        LeftRightMotors.setStopping(brake);
    }

    void doControls() {
        botdrive::control();
        botIntake::control(
            (int)(Controller1.ButtonR1.pressing()) - (int)(Controller1.ButtonR2.pressing())
        );
    }
}