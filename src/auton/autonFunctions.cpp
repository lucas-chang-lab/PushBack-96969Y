#include "Auton/autonFunctions.h"
#include "Utilities/generalUtilities.h"
#include "Utilities/fieldInfo.h"
#include "Utilities/robotInfo.h"
#include "robot-config.h"
#include "AutonUtilities/Pid.h"
#include "Mechanics/topFrontIntake.h"
#include "Mechanics/backIntake.h"
#include "Mechanics/bottomFrontIntake.h"

namespace {
    using namespace genutil;
    void driveVoltage(double leftVoltageVolt, double rightVoltageVolt, double clampMaxVoltage);
}
namespace autonFunctions {
    using namespace genutil;
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

        double leftVelocityFactor = -leftRotationRadiusIn / averageRotationRadiusIn;
        double rightVelocityFactor = rightRotationRadiusIn / averageRotationRadiusIn;

        LeftRightMotors.setStopping(brake);
        PIDControl rotateTargetAnglePid(1, 0.001, 0.4, errorRange);
        timer timeout;
        timeout.reset();
        printf("Starting \n");
        printf("runTimeout seen here = %.2f (seconds)\n", runTimeout);

        while(!rotateTargetAnglePid.isSettled() && timeout.value() < runTimeout) {
            double rotateError = rotation - InertialSensor.rotation(degrees);
            //printf("Rotation: %.2f\n", InertialSensor.rotation(degrees));
            printf("Rotate Error: %.2f\n", rotateError);
            //printf("timeout: %.2f\n", timeout.value());
            rotateTargetAnglePid.computeFromError(rotateError);

            double averageMotorVelocityPct = clamp(rotateTargetAnglePid.getOutput(), -maxVelocityPct, maxVelocityPct);
            printf("rotateTargetAnglePid Output: %.2f\n", rotateTargetAnglePid.getOutput());
            double leftMotorVelocityPct = averageMotorVelocityPct * leftVelocityFactor;
            double rightMotorVelocityPct = averageMotorVelocityPct * rightVelocityFactor;

            driveVoltage(genutil::pctToVolt(leftMotorVelocityPct), genutil::pctToVolt(rightMotorVelocityPct), 12);
            task::sleep(20);   
        }
        printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void driveDistanceTiles(double distanceTiles, double maxVelocityPct, double errorRange, double runTimeout) {
        double targetDistanceInches = distanceTiles * field::tileLengthIn;
        LeftMotors.setPosition(0, rev);
        RightMotors.setPosition(0, rev);

        PIDControl driveTargetDistancePid(4.3, 0, 46, errorRange);
        timer timeout;
        timeout.reset();
        printf("Starting \n");
        while(!driveTargetDistancePid.isSettled() && timeout.value() < runTimeout) {
            double distanceError;
            double traveledRev = (LeftMotors.position(rev) + RightMotors.position(rev)) / 2.0;
            double currentTravelDistanceInches = traveledRev  * trackingLookWheelCircumIn; 
            distanceError = targetDistanceInches - currentTravelDistanceInches;

            //printf("Target Distance: %.2f inches\n", targetDistanceInches);
            printf("Current Distance: %.2f inches\n", currentTravelDistanceInches);
            printf("Distance Error: %.2f inches\n", distanceError);
            printf("Timeout: %.2f seconds\n", timeout.value());
            printf("driveTargetDistancePid Output: %.2f\n", driveTargetDistancePid.getOutput());

            driveTargetDistancePid.computeFromError(distanceError);
            double velocityPct = fmin(maxVelocityPct, fmax(-maxVelocityPct, driveTargetDistancePid.getOutput()));

            double rightVelocityPct = velocityPct;
            double leftVelocityPct = velocityPct;

            driveVoltage(genutil::pctToVolt(leftVelocityPct), genutil::pctToVolt(rightVelocityPct), 10.0);
            task::sleep(20);
        }
        printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void intake2ndStage(int state, double delaySec) {
        topFrontIntake::setState(state, delaySec);
        bottomFrontIntake::setState(-state, delaySec);
        backIntake::setState(-state, delaySec);
    }

    void intake3rdStage(int state, double delaySec) {
        topFrontIntake::setState(-state, delaySec);
        bottomFrontIntake::setState(-state, delaySec);
        backIntake::setState(-state, delaySec);
    }

    void intakeStore(int state, double delaySec) {
        topFrontIntake::setState(state, delaySec);
        bottomFrontIntake::setState(-state, delaySec);
        backIntake::setState(state, delaySec, 6.0);
    }
}

namespace {
    void driveVoltage(double leftVoltageVolt, double rightVoltageVolt, double clampMaxVoltage) {
        double maxVoltage = 12.0;

        double scaleFactor = maxVoltage / fmax(maxVoltage, fmax(fabs(leftVoltageVolt), fabs(rightVoltageVolt)));
        leftVoltageVolt *= scaleFactor;
        rightVoltageVolt *= scaleFactor;

        leftVoltageVolt = clamp(leftVoltageVolt, -clampMaxVoltage, clampMaxVoltage);
        rightVoltageVolt = clamp(rightVoltageVolt, -clampMaxVoltage, clampMaxVoltage);

        LeftMotors.spin(fwd, leftVoltageVolt, voltageUnits::volt);
        RightMotors.spin(fwd, rightVoltageVolt, voltageUnits::volt);
    }
}