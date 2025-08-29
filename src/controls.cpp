#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/botIntake.h"
#include "Mechanics/botIntake2.h"
#include "Mechanics/botIntake3.h"
#include "main.h"


namespace controls {
    void startThreads() {
        static task intakeThread([]() -> int {
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
        botIntake2::control(
            (int)(Controller1.ButtonL1.pressing()) - (int)(Controller1.ButtonL2.pressing())
        );
        botIntake3::control(
            (int)(Controller1.ButtonUp.pressing()) - (int)(Controller1.ButtonDown.pressing())
        );
        // down L2, R2
        if (Controller1.ButtonLeft.pressing()) {
            botIntake::control(-1);
            botIntake2::control(-1);
            botIntake3::control(-1);
        }
    }
}