#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/frontIntake.h"
#include "Mechanics/scorer.h"
#include "Mechanics/botPneumatics.h"
#include "Mechanics/matchLoader.h"
#include "Mechanics/doublePark.h"
#include "main.h"


namespace controls {
    void startThreads() {
        /*task intakeThread([]() -> int {
            frontIntake::runThread();
            return 1;
        });*/
        
        task scorerThread([]() -> int {
            
            scorer::runThread();
            return 1;
        });
    }

    void setUpKeybinds() {
        Controller2.ButtonX.pressed([]() -> void {
            
        });
        Controller1.ButtonX.pressed([]() -> void {
            scorer::filter = !scorer::filter;
        });
        Controller1.ButtonY.pressed([]() -> void {
            matchLoad::switchState();
        });
        Controller1.ButtonA.pressed([]() -> void {
            scorer::locked = false;
            botPneumatics::switchState();
        });
        Controller1.ButtonB.pressed([]() -> void {
            scorer::locked = !scorer::locked;
            botPneumatics::setState(1);
        });
        Controller1.ButtonL2.pressed([]() -> void {

        });
        Controller1.ButtonL1.pressed([]() -> void {

        });
        Controller1.ButtonUp.pressed([]() -> void {
            
        });
        Controller1.ButtonDown.pressed([]() -> void {
            
            doublePark::switchState();
        });

    }

    void preauton() {
        
    }


    void resetStates() {
        LeftRightMotors.setStopping(brake);
    }

    void doControls() {
        botdrive::control();
        // 3rd Stage + 2nd Stage
        frontIntake::control(
            (int)(Controller1.ButtonR2.pressing()) - (int)(Controller1.ButtonR1.pressing())
        );
        if (!scorer::filtering) {
            scorer::control(
                (int)(Controller1.ButtonR2.pressing()) - (int)(Controller1.ButtonR1.pressing())
            );
        }
        
       
        
    }
}