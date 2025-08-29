#include "Mechanics/botIntake3.h"
#include "robot-config.h"
#include "main.h"

namespace {
    bool controlState = true;
}

namespace botIntake3 {
    int _taskState = 0; // 0 = stop, 1 = intake, -1 = outtake
    double _taskDelay = 0;

    void runThread() {
        while (1) {
            
        }
    }

    void preauton() {
        intakeMotor3.stop(hold);
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
        if (canControl()) {
            switch (state)
            {
            case 1:
                intakeMotor3.spin(fwd, 11, volt);
                break;
            case -1:
                intakeMotor3.spin(reverse, 11, volt);
                break;
            default:
                intakeMotor3.stop(coast);
                break;
            }
        } else {
            intakeMotor3.stop(coast);
        }
    }

    bool canControl() {
        return controlState;
    }
}
