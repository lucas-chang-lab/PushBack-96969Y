#pragma once

namespace botArm {
	void setState(bool, double = 0);

	void switchState();

	extern int _taskState;
	extern double _taskDelay;
}
