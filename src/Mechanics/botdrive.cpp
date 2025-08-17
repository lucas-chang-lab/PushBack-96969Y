#include "Mechanics/botDrive.h"

#include "main.h"

namespace {

	void controlArcade();
	void drive(double forwardPct, double rotatePct);
}

namespace botdrive {
	void preauton() {
		LeftMotors.setStopping(brake);
		RightMotors.setStopping(brake);
	}

	void control() {
		controlArcade();
	}
}

namespace {
	void controlArcade() {
		double forward = Controller1.Axis3.position();
		if (fabs(forward) < 2) forward = 0;

		double rotate = Controller1.Axis1.position();  
		if (fabs(rotate) < 2) rotate = 0;

		drive(forward, -rotate * 0.8);
	}

	void drive(double forwardPct, double rotatePct) {
		double leftPct = forwardPct + rotatePct;
		double rightPct = forwardPct - rotatePct;

		double scale = 100.0 / fmax(100.0, fmax(fabs(leftPct), fabs(rightPct)));
		leftPct *= scale;
		rightPct *= scale;

		if (fabs(leftPct) < 5)
			LeftMotors.stop();
		else
			LeftMotors.spin(fwd, 12.0 * (leftPct / 100.0), volt);

		if (fabs(rightPct) < 5)
			RightMotors.stop();
		else
			RightMotors.spin(fwd, 12.0 * (rightPct / 100.0), volt);
	}
}
