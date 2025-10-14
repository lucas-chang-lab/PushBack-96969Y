#include "Mechanics/scorer.h"
#include "robot-config.h"
#include "Mechanics/botPneumatics.h"
#include "main.h"

namespace {
    bool controlState = true;
    bool isRed = false;
    bool isBlue = false;
}

namespace scorer {
    bool filtering = false;
    int _taskState = 0; // 0 = stop, 1 = intake, -1 = outtake
    double _taskDelay = 0;
    bool locked = false;
    bool isSwitchedState = false;
    bool filter = true;
    
    char filterColor = 'b'; // 'r' = red, 'b' = blue, 'n' = none
    void runThread() {
        while (1) {
            if(!locked && canControl()){
                //if(opticalSensor.isNearObject()){
                    double h = opticalSensor.hue();
                    double h2 = opticalSensor.hue();
                    isRed  = ((h >= 0 && h <= 20) || (h >= 340 && h <= 360) || (h2 >= 0 && h2 <= 20) || (h2 >= 340 && h2 <= 360));
                    isBlue =  (h >= 155 && h <= 240) || (h2 >= 155 && h2 <= 240);
                    printf("h = %.2f\n", h);
                    filtering = ((filterColor == 'r' && isRed) || (filterColor == 'b' && isBlue)) && filter;
                    if(filtering) {
                        if (botArmPneumatics.value() == 0 ) {
                            botPneumatics::setState(1);
                            intakeMotor2.spin(reverse, 12, volt);
				            wait(250, msec);
                            botPneumatics::setState(0);
                        } else {
                            intakeMotor2.spin(reverse, 12, volt);
				            wait(250, msec);
                        }
                    }
                //}
            }
            wait(5, msec);
        }
    }

    void preauton() {
        intakeMotor2.stop(hold);
    }

    void setState(int state, double delaySec) {
        if (delaySec <= 1e-9) {
            _taskState = state;
            control(_taskState);
            return;
        }

        _taskState = state;
        _taskDelay = delaySec;

        task setStateTask([]() -> int {
            int taskState = _taskState;
            double taskDelay = _taskDelay;

            task::sleep(taskDelay * 1000);

            control(taskState);
            return 1; 
        });
    }

    void switchState() {
        if (_taskState == 0) {
            setState(1);
        } else {
            setState(0);
        }
    }

    void control(int state) {
        if (locked){
            intakeMotor2.stop(brake);
        }
        else if (canControl()) {
            if (isSwitchedState) {
                state = -state;
            }
            switch (state) {
            case 1:
                intakeMotor2.spin(fwd, 12, volt);
                break;
            case -1:
                intakeMotor2.spin(reverse, 12, volt);
                break;
            default:
                intakeMotor2.stop(brake);
                break;
            }
        } else {
            intakeMotor2.stop(brake);
        }
    }

    bool canControl() {
        return controlState;
    }
}
