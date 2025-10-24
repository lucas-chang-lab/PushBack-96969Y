#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
#include "Auton/preauton.h"
#include "AutonUtilities/odometry.h"
#include "Mechanics/scorer.h"
#include "main.h"

namespace {
    using namespace auton;
    using namespace autonFunctions;
    autonomousType currentAutonType = autonomousType::redRight;
    int auton_allianceId;
    
    void RedRight();
    void RedLeft();
    void BlueRight();
    void BlueLeft();
    void AutonSkill();
    void DrivingSkill();
    void Test();

    bool userRunningAutonomous = false;
}

namespace auton {
    void setAutonRunType(int allianceId, autonomousType autonType) {
        currentAutonType = autonType;
        auton_allianceId = allianceId;
        switch (currentAutonType) {
            case redRight:
                Brain.Screen.print("Auton Type: RedRight");
                scorer::filterColor = 'b';
                break;
            case redLeft:
                Brain.Screen.print("Auton Type: RedLeft");
                scorer::filterColor = 'b';
                break;
            case blueRight:
                Brain.Screen.print("Auton Type: BlueRight");
                scorer::filterColor = 'r';
                break;
            case blueLeft:
                Brain.Screen.print("Auton Type: BlueLeft");
                scorer::filterColor = 'r';
                break;
            case autonSkill:
                Brain.Screen.print("Auton Type: Auton Skill");
                break;
            case drivingSkill:
                Brain.Screen.print("Auton Type: Driving Skill");
                break;
            case test:
                Brain.Screen.print("Auton Type: Test");
                break;
        }
    }

    void showAutonRunType() {
        setAutonRunType(auton_allianceId, currentAutonType);
    }

    autonomousType getAutonRunType() {
        return currentAutonType;
    }

    bool isUserRunningAuton() {
        return userRunningAutonomous;
    }

    void runAutonomous() {
        switch (currentAutonType) {
            case redLeft:
                RedLeft();
                break;
            case redRight:
                RedRight();
                break;
            case blueLeft:
                BlueLeft();
                break;
            case blueRight:
                BlueRight();
                break;
            case autonSkill:
                AutonSkill();
                break;
            case drivingSkill:
                DrivingSkill();
                break;
            case test:
                Test();
                Brain.Screen.printAt(10, 60, "Running Test Auton");
                break;
        }
    }
}

namespace {
    void RedRight() {
        preauton::waitCalibrating();
        odometry::setValues(0,0,0);
    }

    void RedLeft() {
        
        preauton::waitCalibrating();
        odometry::setValues(2,0,-7);
        setRotation(-7);
        intakeStore(1, 0.1);
        driveDistanceTiles(1.4, 50.0, 0.1, 0.8);
        wait(1.5, sec);
        turnToAngle(-140, 0, 1.0, 0.8);
        intake2ndStage(1, 1.2);
        driveDistanceTiles(-0.8, 50.0, 0.1, 0.8);
        wait(1, sec);
        //setMatchLoader(1, 0.4);
        goToPointTiles(0.7, 0.6, 50.0, 0.1, 2.0, true);
        turnToAngle(-180, 0, 1.0, 0.8);
        intakeStore(1, 0);
        wait(1, sec);
        //setMatchLoader(0, 0.2);
        driveDistanceTiles(-2.0, 50.0, 0.1, 0.8);
        intake3rdStage(1, 0);
        wait(1, sec);
    }

    void BlueRight() {

    }

    void BlueLeft() {
        preauton::waitCalibrating();
        odometry::setValues(0,0,0);
        wait(5, sec);
    }

    void AutonSkill() {
        
    }

    void DrivingSkill() {
   
    }

    void Test() {
        preauton::waitCalibrating();
        odometry::setValues(2,0,0);
        setRotation(0);
        goToPointTiles(2, 2, 50.0, 0.1, 5.0, false);
    }
}