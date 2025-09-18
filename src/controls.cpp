#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/backIntake.h"
#include "Mechanics/bottomFrontIntake.h"
#include "Mechanics/topFrontIntake.h"
#include "Mechanics/botPneumatics.h"
#include "main.h"


namespace controls {
    void startThreads() {
        task intakeThread([]() -> int {
            backIntake::runThread();
            return 1;
        });
    }

    void setUpKeybinds() {
        Controller2.ButtonX.pressed([]() -> void {
            botPneumatics::switchState();
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
            topFrontIntake::reverseIntake();
        });

    }

    void preauton() {
        botdrive::preauton();
        controls::startThreads();
        botPneumatics::preauton();
    }


    void resetStates() {
        LeftRightMotors.setStopping(brake);
    }

    void doControls() {
        botdrive::control();
        // 3rd Stage + 2nd Stage
        backIntake::control(
            (int)(Controller1.ButtonR1.pressing()) - (int)(Controller1.ButtonR2.pressing())
        );
        bottomFrontIntake::control(
            (int)(Controller1.ButtonR1.pressing()) - (int)(Controller1.ButtonR2.pressing())
        );
        topFrontIntake::control(
            (int)(Controller1.ButtonR1.pressing()) - (int)(Controller1.ButtonR2.pressing())
        );
        
    }
}