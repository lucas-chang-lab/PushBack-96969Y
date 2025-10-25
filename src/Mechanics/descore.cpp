#include "Mechanics/descore.h"
#include "robot-config.h"
#include "main.h"

namespace {
    bool controlState = true;
}

namespace descore {
    void runThread() {
        while (true) {
            // Thread Code here
            task::sleep(20);
        }
    }

    void preauton() {
        descorePneumatic.set(0);
    }

    void setState(int state, double delaySec) {
		if (delaySec <= 1e-9) {
            descorePneumatic.set(state); 
			return;
		}

		_taskState = state;
		_taskDelay = delaySec;

		task setState([]() -> int {
            int taskState = _taskState;
            double taskDelay = _taskDelay;

            task::sleep(taskDelay * 1000);

            descorePneumatic.set(taskState); 
			return 1;
		});
	}

    void switchState() {
        descorePneumatic.set(!descorePneumatic.value());
	}

	void control(int state) {
		if (canControl()) {
			// Control code here
		}
	}

	bool canControl() {
		return controlState;
	}
    
    int _taskState;
    double _taskDelay;
}

namespace {

}