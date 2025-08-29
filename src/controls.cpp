#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/backIntake.h"
#include "Mechanics/bottomFrontIntake.h"
#include "Mechanics/topFrontIntake.h"
#include "main.h"


namespace controls {
    void startThreads() {
        static task intakeThread([]() -> int {
            backIntake::runThread();
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
        backIntake::control(
            (int)(Controller1.ButtonLeft.pressing()) - (int)(Controller1.ButtonRight.pressing())
        );
        bottomFrontIntake::control(
            (int)(Controller1.ButtonL1.pressing()) - (int)(Controller1.ButtonL2.pressing())
        );
        topFrontIntake::control(
            (int)(Controller1.ButtonUp.pressing()) - (int)(Controller1.ButtonDown.pressing())
        );
        // down L2, R2
        if (Controller1.ButtonR2.pressing()) {
            backIntake::control(1);
            bottomFrontIntake::control(-1);
            topFrontIntake::control(-1);
        }
    }
}