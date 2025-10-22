#pragma once

namespace matchLoad {
	void setState(bool, double = 0);

	void switchState();

	void preauton();

	extern int _taskState;
	extern double _taskDelay;
}
