#include "Auton/preauton.h"

namespace preauton {
    void runPreauton() {
        InertialSensor.calibrate();
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