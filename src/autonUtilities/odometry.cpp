#include "AutonUtilities/odometry.h"
#include "Utilities/robotInfo.h"
#include "Utilities/fieldInfo.h"
#include "main.h"

namespace {
    void odometryThread();

    double x, y, angle;
}


namespace odometry {
    void startThreads() {
        task odometryTask([]() -> int {
            odometryThread();
            return 0;
        });
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    double getAngle() {
        return angle;
    }

    void setValues(double x, double y, double angle) {
        ::x = x; 
        ::y = y;
        ::angle = angle;
    }
}

namespace {
    void odometryThread() {
        double oldLook = (LeftMotors.position(rev) + RightMotors.position(rev)) / 2.0;
        double oldRight = RightRotation.position(rev);
        double oldAngle = InertialSensor.rotation(degrees);
        
        while(true) {
            double newLook = (LeftMotors.position(rev) + RightMotors.position(rev)) / 2.0;
            double newRight = RightRotation.position(rev);
            double newAngle = InertialSensor.rotation(degrees);

            double localDeltaLook = newLook - oldLook;
            double localDeltaRight = newRight - oldRight;
            double deltaAngle = newAngle - oldAngle;

            double averageAngle = oldAngle + deltaAngle / 2.0;
            double rotateAngle = averageAngle * M_PI / 180.0;
            double absoluteDeltaRight = localDeltaRight * cos(rotateAngle) - localDeltaLook * sin(rotateAngle);
            double absoluteDeltaLook = localDeltaRight * sin(rotateAngle) + localDeltaLook * cos(rotateAngle);

            double revToTilesLook = (1.0 / botinfo::driveWheelMotorGearRatio) * botinfo::driveWheelCircumIn / field::tileLengthIn;
            double revToTilesRight = (1.0 / botinfo::trackingLookWheelSensorGearRatio) * botinfo::trackingLookWheelCircumIn / field::tileLengthIn;
            
            x += absoluteDeltaRight * revToTilesRight;
            y += absoluteDeltaLook * revToTilesLook;
            angle = newAngle;

            oldLook = newLook;
            oldRight = newRight;
            oldAngle = newAngle;

            task::sleep(20);
        }
    }
}
