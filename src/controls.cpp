#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/frontIntake.h"
#include "Mechanics/scorer.h"
#include "Mechanics/botPneumatics.h"
#include "Mechanics/trapDoorPneumatics.h"
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
            
        });
        Controller1.ButtonX.pressed([]() -> void {

        });
        Controller1.ButtonY.pressed([]() -> void {
            // scorer::locked = false;
            // scorer::isSwitchedState = !scorer::isSwitchedState;
        });
        Controller1.ButtonA.pressed([]() -> void {
            scorer::locked = false;
            botPneumatics::switchState();
        });
        Controller1.ButtonB.pressed([]() -> void {
            scorer::locked = !scorer::locked;
        });
        Controller1.ButtonL2.pressed([]() -> void {

        });
        Controller1.ButtonL1.pressed([]() -> void {

        });
        Controller1.ButtonUp.pressed([]() -> void {
            
        });
        Controller1.ButtonDown.pressed([]() -> void {
            trapDoor::switchState();
        });

    }

    void preauton() {
        botdrive::preauton();
        controls::startThreads();
        botPneumatics::preauton();
        trapDoor::preauton();
    }


    void resetStates() {
        LeftRightMotors.setStopping(brake);
    }

    void doControls() {
        botdrive::control();
        // 3rd Stage + 2nd Stage
        backIntake::control(
            (int)(Controller1.ButtonR2.pressing()) - (int)(Controller1.ButtonR1.pressing())
        );
        scorer::control(
            (int)(Controller1.ButtonR2.pressing()) - (int)(Controller1.ButtonR1.pressing())
        );
       
        
    }
}