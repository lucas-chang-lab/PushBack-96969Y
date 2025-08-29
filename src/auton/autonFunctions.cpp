#include "Auton/autonFunctions.h"
#include "Utilities/generalUtilities.h"
#include "Utilities/fieldInfo.h"
#include "Utilities/robotInfo.h"
#include "robot-config.h"
#include "AutonUtilities/Pid.h"

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

        double leftVelocityFactor = leftRotationRadiusIn / averageRotationRadiusIn;
        double rightVelocityFactor = -rightRotationRadiusIn / averageRotationRadiusIn;

        LeftRightMotors.setStopping(brake);
        PIDControl rotateTargetAnglePid(1.8, 0.002, 1.7, errorRange);
        timer timeout;
        while(!rotateTargetAnglePid.isSettled() && timeout.value() < runTimeout) {
            double rotateError = rotation - InertialSensor.rotation();
            rotateTargetAnglePid.computeFromError(rotateError);

            double averageMotorVelocityPct = clamp(rotateTargetAnglePid.getOutput(), -maxVelocityPct, maxVelocityPct);
            double leftMotorVelocityPct = averageMotorVelocityPct * leftVelocityFactor;
            double rightMotorVelocityPct = averageMotorVelocityPct * rightVelocityFactor;

            driveVoltage(genutil::pctToVolt(leftMotorVelocityPct), genutil::pctToVolt(rightMotorVelocityPct), 12);
            task::sleep(20);   
        }
        LeftRightMotors.stop(brakeType::brake);
    }

    void driveDistanceTiles(double distanceTiles, double maxVelocityPct, double errorRange, double runTimeout) {
        driveAndTurnDistanceTiles(distanceTiles, InertialSensor.rotation(), maxVelocityPct, 100.0, errorRange, runTimeout);
    }

    void driveAndTurnDistanceTiles(double distanceTiles, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        driveAndTurnDistanceWithInches(distanceTiles * field::tileLengthIn, targetRotation, maxVelocityPct, maxTurnVelocityPct, errorRange * field::tileLengthIn, runTimeout);
    }

    void driveAndTurnDistanceTilesMotionProfile(double distanceTiles, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning with motion profile in tiles
    }

    void driveAndTurnDistanceWithInches(double distanceInches, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        //double lookEncoderInitialRev = LookEncoder.rotation(rev);
        double lookRotationInitialRev = LookRotation.position(rev);
        //double rightRotationInitialRev = RightRotation.position(rev);

        PIDControl driveTargetDistancePid(12.5, 0, 80, errorRange);
		PIDControl rotateTargetAnglePid(1.0, 0.001, 0.5, defaultTurnAngleErrorRange);
		PIDControl synchronizeVelocityPid(0.4, 0, 0, 5.0);

        timer timeout;

        while(!(driveTargetDistancePid.isSettled() && rotateTargetAnglePid.isSettled()) && timeout.value() < runTimeout) {
            double distanceError;
            double targetDistanceInches = distanceInches;
            double lookCurrentRotation = LookRotation.position(rev) - lookRotationInitialRev;
            double currentTravelDistanceInches = lookCurrentRotation / trackingLookWheelSensorGearRatio * trackingLookWheelCircumIn; 
            distanceError = targetDistanceInches - currentTravelDistanceInches;

            driveTargetDistancePid.computeFromError(distanceError);
            double velocityPct = fmin(maxVelocityPct, fmax(-maxVelocityPct, driveTargetDistancePid.getOutput()));

            double rotateError = (targetRotation - InertialSensor.rotation());
            rotateTargetAnglePid.computeFromError(rotateError);
            double rotateVelocityPct = fmin(maxTurnVelocityPct, fmax(-maxTurnVelocityPct, rotateTargetAnglePid.getOutput()));


            double leftVelocityPct = velocityPct + rotateVelocityPct;
            double rightVelocityPct = velocityPct - rotateVelocityPct;

            driveVoltage(genutil::pctToVolt(leftVelocityPct), genutil::pctToVolt(rightVelocityPct), 10.0);
        }

    
    }

    void driveAndTurnDistanceWithInchesMotionProfile(double distanceInches, double targetRotation, double maxVelocityPct, double maxTurnVelocityPct, double errorRange, double runTimeout) {
        // Implementation for driving and turning with motion profile in inches
    }

    void setIntakeState(int state, double delaySec) {
        // Implementation for setting the intake state
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