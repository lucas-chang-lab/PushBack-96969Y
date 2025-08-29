#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
#include "main.h"

namespace {
    using namespace auton;
    using namespace autonFunctions;
    autonomousType currentAutonType = autonomousType::redUp;
    int auton_allianceId;
    
    void runAutonRedUp();
    void runAutonRedDown();
    void runAutonBlueUp();
    void runAutonBlueDown();
    void runAutonSkill();
    void runDrivingSkill();
    void runTestAuton();

    bool userRunningAutonomous = true;
}

namespace auton {
    void setAutonRunType(int allianceId, autonomousType autonType) {
        currentAutonType = autonType;
        auton_allianceId = allianceId;
        switch (currentAutonType) {
            case redUp:
                Brain.Screen.print("Auton Type: Red Up");
                break;
            case redDown:
                Brain.Screen.print("Auton Type: Red Down");
                break;
            case blueUp:
                Brain.Screen.print("Auton Type: Blue Up");
                break;
            case blueDown:
                Brain.Screen.print("Auton Type: Blue Down");
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
        Brain.Screen.printAt(10, 110, "hehe");
        switch (currentAutonType) {
            case redUp:
                runAutonRedUp();
                break;
            case redDown:
                runAutonRedDown();
                break;
            case blueUp:
                runAutonBlueUp();
                break;
            case blueDown:
                runAutonBlueDown();
                break;
            case autonSkill:
                runAutonSkill();
                break;
            case drivingSkill:
                runDrivingSkill();
                break;
            case test:
                runTestAuton();
                Brain.Screen.printAt(10, 60, "Running Test Auton");
                break;
        }
    }
}

namespace {
    void runAutonRedUp() {
        Brain.Screen.printAt(10, 70, "Running Red Up Auton");
        driveDistanceTiles(1.0, 100.0);
    }

    void runAutonRedDown() {
        // Implement Red Down autonomous logic
    }

    void runAutonBlueUp() {
        // Implement Blue Up autonomous logic
    }

    void runAutonBlueDown() {
        // Implement Blue Down autonomous logic
    }

    void runAutonSkill() {
        // Implement Auton Skill logic
    }

    void runDrivingSkill() {
        // Implement Driving Skill logic
    }

    void runTestAuton() {
        // Implement Test Auton logic
    }
}