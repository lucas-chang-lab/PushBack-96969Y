#include "AutonUtilities/Pid.h"
#include "Mechanics/botDrive.h"
#include "Utilities/robotInfo.h"
#include "main.h"   

namespace {
    using namespace botinfo;
    using namespace std;
    using botdrive::controlType;

    void controlArcadeTwoStick();
    void controlArcadeSingleStick();
    void drive(double initLeftPct, double initRightPct, double initPolarRotatePct, double rotateCenterOffsetIn = 0);

    controlType driveMode = controlType::ArcadeTwoStick;
    bool driveModeDebounce = false;

    double maxDriveVelocityPct = 100.0;
}

namespace botdrive {
    void preauton() {
        LeftMotors.setStopping(brake);
        RightMotors.setStopping(brake);
    }

    void switchDriveMode() {
        if (!driveModeDebounce) {
            driveModeDebounce = true;

            switch(driveMode) {
                case controlType::ArcadeTwoStick:
                    driveMode = controlType::ArcadeSingleStick;
                    break;
                case controlType::ArcadeSingleStick:
                    driveMode = controlType::ArcadeTwoStick;
                    break;
                default:
                    break;
            }
            
            task::sleep(100);
            driveModeDebounce = false;
        }
    }

    void control() {
        switch(driveMode) {
            case controlType::ArcadeTwoStick:
                controlArcadeTwoStick();
                break;
            case controlType::ArcadeSingleStick:
                controlArcadeSingleStick();
                break;
            default:
                break;
        }
    }

    void setMaxDriveVelocity(double velocityPct) {
        maxDriveVelocityPct = velocityPct;
    }

    double getMaxDriveVelocity() {
        return maxDriveVelocityPct;
    }
}

namespace {
    /// @brief Drive in arcade mode (Axis3 forward/backward, Axis1 rotation)
    void controlArcadeTwoStick() {
        double axis3 = Controller1.Axis3.position();
        if (fabs(axis3) < 2) axis3 = 0;
    
        double axis1 = Controller1.Axis1.position();
        if (fabs(axis1) < 2) axis1 = 0;

        drive(axis3, axis3, axis1 * 0.8);
    }

    /// @brief Drive in arcade mode (Axis3 forward/backward, Axis4 rotation)
    void controlArcadeSingleStick() {
        double axis3 = Controller1.Axis3.position();
        if (fabs(axis3) < 2) axis3 = 0;
    
        double axis4 = Controller1.Axis4.position();
        if (fabs(axis4) < 2) axis4 = 0;

        drive(axis3, axis3, axis4);
    }

    void drive(double initLeftPct, double initRightPct, double initPolarRotatePct, double rotateCenterOffsetIn) {
        double leftRotateRadiusIn = halfRobotLengthIn + rotateCenterOffsetIn;
        double rightRotateRadiusIn = halfRobotLengthIn - rotateCenterOffsetIn;
        double leftPolarRotatePct =  initPolarRotatePct * (leftRotateRadiusIn / halfRobotLengthIn);
        double rightPolarRotatePct = initPolarRotatePct * (rightRotateRadiusIn / halfRobotLengthIn);

        double leftPct = initLeftPct + leftPolarRotatePct;
        double rightPct = initRightPct - rightPolarRotatePct;

        double scaleFactor = -maxDriveVelocityPct / fmax(maxDriveVelocityPct, fmax(abs(leftPct), fabs(rightPct)));
        leftPct *= scaleFactor;
        rightPct *= scaleFactor;
        if (fabs(rightPct) < 5) {
            RightMotors.stop(brake);
        } else {
            RightMotors.spin(fwd, 12.7 * (rightPct / 100.0), volt);
        }

        if (fabs(leftPct) < 5) {
            LeftMotors.stop(brake);
        } else {
            LeftMotors.spin(fwd, 12.7 * (leftPct / 100.0), volt);
        }
        
    }
}