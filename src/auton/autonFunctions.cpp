#include "auton/autonFunctions.h"
#include "Utilities/generalUtilities.h"
#include "Utilities/fieldInfo.h"
#include "Utilities/robotInfo.h"
#include "robot-config.h"
#include "autonUtilities/Pid.h"

namespace autonFunctions {
    using namespace botinfo;
    void setRotation(double rotation) {
        InertialSensor.setRotation(rotation, rotationUnits::deg);
    }

    void turnToAngle(double rotation, double rotateCenterOffsetIn, double errorRange, double runTimeout) {
        turnToAngleVelocity(rotation, 100.0, rotateCenterOffsetIn, errorRange, runTimeout);
    }

    void turnToAngleVelocity(double rotation, double maxVelocityPct, double rotateCenterOffsetIn, double errorRange, double runTimeout) {
        double leftRotationRadiusIn = halfRobotLengthIn + rotateCenterOffsetIn;
        double rightRotationRadiusIn = halfRobotLengthIn - rotateCenterOffsetIn;
        double averageRotationRadiusIn = (leftRotationRadiusIn + rightRotationRadiusIn) / 2.0;

        double leftVelocityFactor = leftRotationRadiusIn / averageRotationRadiusIn;
        double rightVelocityFactor = -rightRotationRadiusIn / averageRotationRadiusIn;

        LeftRightMotors.setStopping(brake);
        Pid rotateTargetAnglePid(1.8, 0.002, 1.7, errorRange);
        

    }

    void driveDistanceTiles(double distanceTiles, double maxVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving a certain distance in tiles
    }

    void driveAndTurnDistanceTiles(double distanceTiles, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning a certain distance in tiles
    }

    void driveAndTurnDistanceTilesMotionProfile(double distanceTiles, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning with motion profile in tiles
    }

    void driveAndTurnDistanceWithInches(double distanceInches, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning a certain distance in inches
    }

    void driveAndTurnDistanceWithInchesMotionProfile(double distanceInches, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning with motion profile in inches
    }

    void setIntakeState(int state, double delaySec) {
        // Implementation for setting the intake state
    }
}