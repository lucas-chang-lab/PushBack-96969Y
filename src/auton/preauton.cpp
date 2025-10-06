#include "Auton/preauton.h"
#include "Mechanics/botPneumatics.h"
#include "AutonUtilities/odometry.h"

namespace preauton {
    void runPreauton() {
        InertialSensor.calibrate();
        botPneumatics::setState(1);
    }
    void waitCalibrating() {
        while (InertialSensor.isCalibrating()) vex::this_thread::sleep_for(20);
        vex::this_thread::sleep_for(200);
        printf("Inertial Sensor Calibrated \n");
    }

    bool isPreautonFinished() {
        return !InertialSensor.isCalibrating();
    }
}