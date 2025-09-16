#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
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

    bool userRunningAutonomous = true;
}

namespace auton {
    void setAutonRunType(int allianceId, autonomousType autonType) {
        currentAutonType = autonType;
        auton_allianceId = allianceId;
        switch (currentAutonType) {
            case redRight:
                Brain.Screen.print("Auton Type: RedRight");
                break;
            case redLeft:
                Brain.Screen.print("Auton Type: RedLeft");
                break;
            case blueRight:
                Brain.Screen.print("Auton Type: BlueRight");
                break;
            case blueLeft:
                Brain.Screen.print("Auton Type: BlueLeft");
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
        setRotation(0.0);

        //turnToAngle(90, 0, 2.0, 2);
        //turnToAngle(0, 0, 5.0, 10);
        driveDistanceTiles(1.0, 80.0, 0.1, 2);
    }

    void RedLeft() {
        setRotation(-10.0);
        driveDistanceTiles(1.5, 90.0);
        turnToAngle(-135);
        driveDistanceTiles(1.5, 90.0);
        turnToAngle(0);
        driveDistanceTiles(1.0, 90.0);
    }

    void BlueRight() {
        
    }

    void BlueLeft() {
        
    }

    void AutonSkill() {
        
    }

    void DrivingSkill() {
   
    }

    void Test() {
   
    }
}