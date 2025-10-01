#include "Utilities/generalUtilities.h"
#include "Utilities/robotInfo.h"
#include "Utilities/fieldInfo.h"
#include "AutonUtilities/odometry.h"
#include "main.h"

namespace genutil {
    double clamp (double value, double min, double max) {
        return fmax(fmin(value, max), min);
    }

    double pctToVolt(double pct) {
        return (pct * 12.0) / 100.0;
    }

    double voltToPct(double volt) {
        return (volt * 100.0) / 12.0;
    }

    double degToRad(double degrees) {
        return degrees* (M_PI / 180.0);
    }

    double radToDeg(double radians) {
        return radians * (180.0 / M_PI);
    }

    bool isWithin(double value, double target, double withinRange) {
        return fabs(value - target) <= withinRange;
    }

    int signum(double value) {
        return (value > 0) - (value < 0);
    }

    double wrapAngle(double angle) {
        while(angle > 180.0) angle -= 360.0;
        while(angle < -180.0) angle += 360.0;
        return angle;
    }

    void distanceTesting() {
        double LeftStart = LeftMotors.position(rev);
        double RightStart = RightMotors.position(rev);
        while(1) {
            double revs = (LeftMotors.position(rev) - LeftStart + RightMotors.position(rev) - RightStart) / 2.0;
            printf("driveWheel: %.2f tiles\n", (revs / botinfo::driveWheelMotorGearRatio * botinfo::driveWheelCircumIn / field::tileLengthIn));
            //printf("trackingWheel: %.2f tiles\n", (revs / botinfo::trackingLookWheelSensorGearRatio * botinfo::trackingLookWheelCircumIn / field::tileLengthIn));
        }
    }

    void odometryTesting() {
        while(1) {
            printf("X: %.2f tiles, Y: %.2f tiles, Angle: %.2f degrees\n", odometry::getX(), odometry::getY(), odometry::getAngle());
            vex::this_thread::sleep_for(100);
        }
    }
}