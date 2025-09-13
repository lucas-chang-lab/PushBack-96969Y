#pragma once

#include "Auton/autonValues.h"

namespace autonFunctions {
    using namespace autonvals;

    void setRotation(double rotation);
    void turnToAngle(double rotation, double rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 30.0);
    void turnToAngleVelocity(double rotation, double maxVelocityPct = 100.0, double rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 30.0);
    void driveDistanceTiles(double distanceTiles, double maxVelocityPct = 100, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3.0);
}