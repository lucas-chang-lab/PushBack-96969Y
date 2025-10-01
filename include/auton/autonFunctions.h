#pragma once

#include "Auton/autonValues.h"

namespace autonFunctions {
    using namespace autonvals;

    void setRotation(double rotation);
    void turnToAngle(double rotation, double rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 30.0);
    void turnToAngleVelocity(double rotation, double maxVelocityPct = 100.0, double rotateCenterOffsetIn = 0, double errorRange = defaultTurnAngleErrorRange, double runTimeout = 30.0);
    void driveDistanceTiles(double distanceTiles, double maxVelocityPct = 100, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3.0);
    void driveAndTurnDistanceTiles(double distanceTiles, double rotation, double maxVelocityPct = 100.0, double maxTurnVelocityPct = 100.0, double rotateCenterOffsetIn = 0, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 3.0);
    void goToPoseTiles(double targetX, double targetY, double targetAngle, double maxPct = 100.0, double errorRange = defaultMoveTilesErrorRange, double runTimeout = 5.0);

    void intake3rdStage(int state, double delaySec = 0);
    void intake2ndStage(int state, double delaySec = 0);
    void intake1stStage(int state, double delaySec = 0);
    void intakeStore(int state, double delaySec = 0);
}