#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
#include "main.h"

namespace {
    using namespace auton;
    using namespace autonFunctions;
    autonomousType currentAutonType = autonomousType::redLeft;
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
        //driveDistanceTiles(1.5, 100.0);
        turnToAngle(20.0);
        //driveDistanceTiles(1.0, 100.0);
        //turnToAngle(-120);
    }

    void RedRight() {
        setRotation(0.0);
        driveDistanceTiles(1.5, 100.0);
        turnToAngle(60.0);
        driveDistanceTiles(1.0, 100.0);
        turnToAngle(-120);    }

    void BlueLeft() {
        setRotation(0.0);
        driveDistanceTiles(1.5, 100.0);
        turnToAngle(60.0);
        driveDistanceTiles(1.0, 100.0);
        turnToAngle(-120);
    }

    void BlueRight() {
        setRotation(0.0);
        driveDistanceTiles(1.5, 100.0);
        turnToAngle(60.0);
        driveDistanceTiles(1.0, 100.0);
        turnToAngle(-120);
    }

    void AutonSkill() {
        // Implement Auton Skill logic
    }

    void DrivingSkill() {
        // Implement Driving Skill logic
    }

    void Test() {
        // Implement Test Auton logic
    }
}