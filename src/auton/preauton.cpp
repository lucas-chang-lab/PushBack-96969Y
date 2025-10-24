#include "Auton/preauton.h"
#include "Mechanics/botPneumatics.h"
#include "AutonUtilities/odometry.h"
#include "Mechanics/matchLoader.h"
#include "Mechanics/scorer.h"
#include "Mechanics/botDrive.h"
#include "robot-config.h"

#include "controls.h"

namespace preauton {
    void runPreauton() {
        InertialSensor.calibrate();
        botPneumatics::setState(1);

        odometry::startThreads();
        
        controls::preauton();
        controls::startThreads();

        opticalSensor.setLight(ledState::on); 
        opticalSensor.setLightPower(30);
        
        botdrive::preauton(); 
        
        botPneumatics::preauton();
        matchLoad::preauton();
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