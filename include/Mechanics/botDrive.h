#pragma once

namespace botdrive {
	enum controlType {
		ArcadeTwoStick,
		ArcadeSingleStick,
	};

	void preauton();

	void switchDriveMode();

	void control();
}