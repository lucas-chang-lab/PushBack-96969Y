#include "Mechanics/botIntake.h"
#include "robot-config.h"
#include "main.h"

namespace
{
    bool controlState = true;
}

namespace botIntake
{
    int _taskState = 0; // 0 = stop, 1 = intake, -1 = outtake
    double _taskDelay = 0;

    void runThread()
    {
        while (true)
        {
            
        }
    }

    void preauton()
    {
        intakeMotor.stop(hold);
    }

    void setState(int state, double delaySec)
    {

        if (delaySec <= 1e-9)
        {
            _taskState = state;
            control(_taskState);
            return;
        }

        _taskState = state;
        _taskDelay = delaySec;

        task setStateTask([]() -> int
        {
            int taskState = _taskState;
            double taskDelay = _taskDelay;

            task::sleep(taskDelay * 1000);

            control(taskState);
            return 1; 
        });
    }

    void switchState()
    {
        if (_taskState == 0) {
            setState(1);
        } else {
            setState(0);
        }
    }

    void control(int state)
    {
        if (canControl())
        {
            switch (state)
            {
            case 1:
                intakeMotor.spin(fwd, 11, volt);
                break;
            case -1:
                intakeMotor.spin(reverse, 11, volt);
                break;
            default:
                intakeMotor.stop(hold);
                break;
            }
        }
        else
        {
            intakeMotor.stop(hold);
        }
    }

    bool canControl()
    {
        return controlState;
    }
}
