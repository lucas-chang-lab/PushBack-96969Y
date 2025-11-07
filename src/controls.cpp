#include "controls.h"
#include "Mechanics/botDrive.h"
#include "Mechanics/frontIntake.h"
#include "Mechanics/scorer.h"
#include "Mechanics/botPneumatics.h"
#include "Mechanics/matchLoader.h"
#include "Mechanics/doublePark.h"
#include "Mechanics/descore.h"
#include "main.h"
#include "Graphic/img.h"


namespace controls {
    int show = 0;
    void startThreads() {
        task scorerThread([]() -> int {
            
            //scorer::runThread();
            return 1;
        });
    }

    void setUpKeybinds() {
        Controller1.ButtonX.pressed([]() -> void {
            scorer::filter = !scorer::filter;
        });
        Controller1.ButtonY.pressed([]() -> void {
            
        });
        Controller1.ButtonA.pressed([]() -> void {
            scorer::locked = false;
            botPneumatics::switchState();
        });
        Controller1.ButtonB.pressed([]() -> void {
            scorer::locked = !scorer::locked;
            botPneumatics::setState(1);
        });
        Controller1.ButtonL2.pressed([]() -> void{
            matchLoad::switchState(); 
        });
        Controller1.ButtonL1.pressed([]() -> void {
            descore::switchState();
        });
        Controller1.ButtonUp.pressed([]() -> void {
        });
        Controller1.ButtonDown.pressed([]() -> void {
            
            doublePark::switchState();
        });
        Controller1.ButtonLeft.pressed([]() -> void { 
            /*show++;
            switch(show){
            case 1:
                img::drawLogo();
                break;
            case 2:
                img::drawLogo2();
                break;
            default:
                show = 0;
                Brain.Screen.clearScreen();
                break;
            }*/
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