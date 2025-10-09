#include "Mechanics/scorer.h"
#include "robot-config.h"
#include "main.h"

namespace {
    bool controlState = true;
}

namespace scorer {
    int _taskState = 0; // 0 = stop, 1 = intake, -1 = outtake
    double _taskDelay = 0;
    bool locked = false;
    bool isSwitchedState = false;

    void runThread() {
        while (1) {
            
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
