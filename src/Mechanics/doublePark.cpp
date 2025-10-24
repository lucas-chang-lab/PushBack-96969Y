#include "Mechanics/doublePark.h"
#include "main.h"

namespace {
    bool controlState = true;
}

namespace doublePark {
    void runThread() {
        while (true) {
            task::sleep(20);
        }
    }

    void preauton() {

    }

    void setState(int state, double delaySec) {
		if (delaySec <= 1e-9) {
            doubleParkPneumatic.set(state); // Example action
			return;
		}

		_taskState = state;
		_taskDelay = delaySec;

		task setState([]() -> int {
			int taskState = _taskState;
            double taskDelay = _taskDelay;

            task::sleep(taskDelay * 1000);

            doubleParkPneumatic.set(taskState); // Example action
            return 1; 
		});
	}

    void switchState() {
		doubleParkPneumatic.set(!doubleParkPneumatic.value());
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