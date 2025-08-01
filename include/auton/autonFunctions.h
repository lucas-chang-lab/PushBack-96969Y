#pragma once

#include "Auton/autonValues.h"

namespace autonFunctions {
    using autonvals::defaultMoveTilesErrorRange, autonvals::defaultMoveWithInchesErrorRange, autonvals::defaultTurnAngleErrorRange;

    void setRotation(double rotation);
    void turnToAngle(double rotation, double rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 3.0);
    void turnToAngleVelocity(double rotation, double maxVelocityPct = 100.0, doublt rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 3.0);
    void driveDistanceTiles(double distanceTiles, double maxVelocityPct = 100, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3.0);
	void driveAndTurnDistanceTiles(double distanceTiles, double targetRotation, double maxVelocityPct = 100, double maxTurnVelocityPct = 100, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3);
	void driveAndTurnDistanceTilesMotionProfile(double distanceTiles, double targetRotation, double maxVelocityPct = 100, double maxTurnVelocityPct = 100, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3);
	void driveAndTurnDistanceWithInches(double distanceInches, double targetRotation, double maxVelocityPct = 100, double maxTurnVelocityPct = 100, double errorRange = defaultMoveWithInchesErrorRange, double runTimeout = 3);
	void driveAndTurnDistanceWithInchesMotionProfile(double distanceInches, double targetRotation, double maxVelocityPct = 100, double maxTurnVelocityPct = 100, double errorRange = defaultMoveWithInchesErrorRange, double runTimeout = 3);

	void setIntakeState(int state, double delaySec = 0);
}