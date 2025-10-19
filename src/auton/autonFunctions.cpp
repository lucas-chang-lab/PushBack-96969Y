#include "Auton/autonFunctions.h"
#include "Utilities/generalUtilities.h"
#include "Utilities/fieldInfo.h"
#include "Utilities/robotInfo.h"
#include "robot-config.h"
#include "AutonUtilities/Pid.h"
#include "Mechanics/frontIntake.h"
#include "Mechanics/scorer.h"
#include "AutonUtilities/odometry.h"

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
        PIDControl rotateTargetAnglePid(1, 0.001, 0.4, errorRange);
        timer timeout;
        timeout.reset();
        //printf("Starting \n");
        //printf("runTimeout seen here = %.2f (seconds)\n", runTimeout);

        while(!rotateTargetAnglePid.isSettled() && timeout.value() < runTimeout) {
            double rotateError = rotation - InertialSensor.rotation(degrees);
            //printf("Rotation: %.2f\n", InertialSensor.rotation(degrees));
            //printf("Rotate Error: %.2f\n", rotateError);
            //printf("timeout: %.2f\n", timeout.value());
            rotateTargetAnglePid.computeFromError(rotateError);

            double averageMotorVelocityPct = clamp(rotateTargetAnglePid.getOutput(), -maxVelocityPct, maxVelocityPct);
            //printf("rotateTargetAnglePid Output: %.2f\n", rotateTargetAnglePid.getOutput());
            double leftMotorVelocityPct = averageMotorVelocityPct * leftVelocityFactor;
            double rightMotorVelocityPct = averageMotorVelocityPct * rightVelocityFactor;

            // opposite direction
            driveVoltage(-genutil::pctToVolt(leftMotorVelocityPct), -genutil::pctToVolt(rightMotorVelocityPct), 12);
            task::sleep(20);   
        }
        //printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void driveDistanceTiles(double distanceTiles, double maxVelocityPct, double errorRange, double runTimeout) {
        double targetDistanceInches = distanceTiles * field::tileLengthIn;
        LeftMotors.setPosition(0, rev);
        RightMotors.setPosition(0, rev);

        PIDControl driveTargetDistancePid(4.3, 0, 46, errorRange);
        timer timeout;
        timeout.reset();
        //printf("Starting \n");
        while(!driveTargetDistancePid.isSettled() && timeout.value() < runTimeout) {
            double distanceError;
            double traveledRev = -(LeftMotors.position(rev) + RightMotors.position(rev)) / 2.0;
            double currentTravelDistanceInches = traveledRev  *  driveWheelCircumIn; 
            distanceError = targetDistanceInches - currentTravelDistanceInches;

            //printf("Target Distance: %.2f inches\n", targetDistanceInches);
            //printf("Current Distance: %.2f inches\n", currentTravelDistanceInches);
            //printf("Distance Error: %.2f inches\n", distanceError);
            //printf("Timeout: %.2f seconds\n", timeout.value());
            //printf("driveTargetDistancePid Output: %.2f\n", driveTargetDistancePid.getOutput());

            driveTargetDistancePid.computeFromError(distanceError);
            double velocityPct = fmin(maxVelocityPct, fmax(-maxVelocityPct, driveTargetDistancePid.getOutput()));

            double rightVelocityPct = velocityPct;
            double leftVelocityPct = velocityPct;

            driveVoltage(-genutil::pctToVolt(leftVelocityPct), -genutil::pctToVolt(rightVelocityPct), 10.0);
            task::sleep(20);
        }
        //printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void driveAndTurnDistanceTiles(double distanceTiles, double rotation, double maxVelocityPct, double maxTurnVelocityPct, double rotateCenterOffsetIn, double errorRange, double runTimeout) {
        double targetDistanceInches = distanceTiles * field::tileLengthIn;
        LeftMotors.setPosition(0, rev);
        RightMotors.setPosition(0, rev);

        double leftRotationRadiusIn = halfRobotLengthIn + rotateCenterOffsetIn;
        double rightRotationRadiusIn = halfRobotLengthIn - rotateCenterOffsetIn;
        double averageRotationRadiusIn = (leftRotationRadiusIn + rightRotationRadiusIn) / 2.0;

        double leftVelocityFactor = leftRotationRadiusIn / averageRotationRadiusIn;
        double rightVelocityFactor = -rightRotationRadiusIn / averageRotationRadiusIn;

        PIDControl driveTargetDistancePid(4.3, 0, 46, errorRange);
        PIDControl rotateTargetAnglePid(1, 0.001, 0.4, defaultTurnAngleErrorRange);
        timer timeout;
        timeout.reset();
        printf("Starting \n");
        while((!driveTargetDistancePid.isSettled() || !rotateTargetAnglePid.isSettled()) && timeout.value() < runTimeout) {
            double distanceError;
            double traveledRev = -(LeftMotors.position(rev) + RightMotors.position(rev)) / 2.0;
            double currentTravelDistanceInches = traveledRev  * driveWheelCircumIn; 
            distanceError = targetDistanceInches - currentTravelDistanceInches;

            double rotateError = rotation - InertialSensor.rotation(degrees);

            //printf("Target Distance: %.2f inches\n", targetDistanceInches);
            //printf("Current Distance: %.2f inches\n", currentTravelDistanceInches);
            //printf("Distance Error: %.2f inches\n", distanceError);
            //printf("Rotate Error: %.2f\n", rotateError);
            //printf("Timeout: %.2f seconds\n", timeout.value());
            //printf("driveTargetDistancePid Output: %.2f\n", driveTargetDistancePid.getOutput());
            //printf("rotateTargetAnglePid Output: %.2f\n", rotateTargetAnglePid.getOutput());

            driveTargetDistancePid.computeFromError(distanceError);
            rotateTargetAnglePid.computeFromError(rotateError);
            
            double velocityPct = fmin(maxVelocityPct, fmax(-maxVelocityPct, driveTargetDistancePid.getOutput()));
            double rotationPct = fmin(maxTurnVelocityPct, fmax(-maxTurnVelocityPct, rotateTargetAnglePid.getOutput()));
            double leftMotorVelocityPct = velocityPct + rotationPct * leftVelocityFactor;
            double rightMotorVelocityPct = velocityPct + rotationPct * rightVelocityFactor;

            driveVoltage(-genutil::pctToVolt(leftMotorVelocityPct), -genutil::pctToVolt(rightMotorVelocityPct), 10.0);
            task::sleep(20);
        }
        printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void goToPoseTiles(double targetX, double targetY, double targetAngle, double maxPct, double errorRange, double runTimeout) {
        LeftMotors.setPosition(0, rev);
        RightMotors.setPosition(0, rev);

        PIDControl driveTargetDistancePid(12, 0.08, 0.3, errorRange);
        PIDControl faceTargetPid(0.8, 0, 0.2, 10.0);
        PIDControl rotateTargetAnglePid(1, 0.001, 0.4, defaultTurnAngleErrorRange);
        timer timeout;
        timeout.reset();
        printf("Starting \n");
        while((!driveTargetDistancePid.isSettled() || !rotateTargetAnglePid.isSettled()) && timeout.value() < runTimeout) {
            double currentX = odometry::getX();
            double currentY = odometry::getY();
            double currentAngle = odometry::getAngle();

            double deltaX = targetX - currentX;
            double deltaY = targetY - currentY;
            double distanceError = sqrt(deltaX * deltaX + deltaY * deltaY);

            double angleToTarget = atan2(deltaX, deltaY) * 180.0 / M_PI; //here
            double angleError = angleToTarget - currentAngle;
            angleError = genutil::wrapAngle(angleError);

            double rotateError = targetAngle - currentAngle;
            rotateError = genutil::wrapAngle(rotateError);

    
            printf("Distance Error: %.2f tiles\n", distanceError);
            printf("Angle to Target: %.2f degrees\n", angleToTarget);
            //printf("Angle Error: %.2f degrees\n", angleError);
            //printf("Rotate Error: %.2f degrees\n", rotateError);
            //printf("Timeout: %.2f seconds\n", timeout.value());
            printf("driveTargetDistancePid Output: %.2f\n", driveTargetDistancePid.getOutput());
            printf("faceTargetPid Output: %.2f\n", faceTargetPid.getOutput());
            //printf("rotateTargetAnglePid Output: %.2f\n", rotateTargetAnglePid.getOutput());

            driveTargetDistancePid.computeFromError(distanceError);
            double velocityPct = fmin(maxPct, fmax(-maxPct, driveTargetDistancePid.getOutput()));

            double rotationPct;
            if (distanceError > errorRange) {
                faceTargetPid.computeFromError(angleError);
                rotationPct = fmin(maxPct, fmax(-maxPct, faceTargetPid.getOutput()));
            } else {
                rotateTargetAnglePid.computeFromError(rotateError);
                rotationPct = fmin(maxPct, fmax(-maxPct, rotateTargetAnglePid.getOutput()));
            }

            double leftMotorVelocityPct = velocityPct + rotationPct;
            double rightMotorVelocityPct = velocityPct - rotationPct;   
            driveVoltage(-genutil::pctToVolt(leftMotorVelocityPct), -genutil::pctToVolt(rightMotorVelocityPct), 12.0);
            task::sleep(20);
        }
        printf("Ending \n");
        LeftRightMotors.stop(brakeType::brake);
    }

    void intake3rdStage(int state, double delaySec) {
        scorer::setState(-state, delaySec);
        frontIntake::setState(-state, delaySec);
    }

    void intake2ndStage(int state, double delaySec) {
        scorer::setState(-state, delaySec);
        frontIntake::setState(-state, delaySec);
    }

    void intake1stStage(int state, double delaySec) {
        scorer::setState(state, delaySec);
        frontIntake::setState(state, delaySec);
    }

    void intakeStore(int state, double delaySec) {
        scorer::setState(state, delaySec);
        frontIntake::setState(-state, delaySec);
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