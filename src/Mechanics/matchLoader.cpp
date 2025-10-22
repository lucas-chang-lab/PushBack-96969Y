#include "Mechanics/matchLoader.h"
#include "robot-config.h"
#include "main.h"

namespace matchLoad {
	int _taskState = 0; // 0 = closed, 1 = open
	double _taskDelay = 0;
	void setState(bool state, double delaySec) {
		// Check for instant set
		if (delaySec <= 1e-9) {
			// Set state here
			matchLoader.set(state);

			return;
		}

		// Set global variables
		_taskState = state;
		_taskDelay = delaySec;

		task setState([]() -> int {
			// Get global variables
			int taskState = _taskState;
			double taskDelay = _taskDelay;

			// Delay setting state
			task::sleep(taskDelay * 1000);

			// Set state here
			matchLoader.set(taskState);

			return 1;
		});
	}

	void switchState() {
		setState(!matchLoader.value());
	}

	void preauton() {
		matchLoader.set(0);
	}
}
