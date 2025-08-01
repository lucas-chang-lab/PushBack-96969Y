#include "auton/auton.h"
#include "main.h"

namespace {
    using namespace auton;
    autonomousType currentAutonType = autonomousType::test;
    
    void runAutonRedUp();
    void runAutonRedDown();
    void runAutonBlueUp();
    void runAutonBlueDown();
    void runAutonSkill();
    void runDrivingSkill();
    void runTestAuton();
}

namespace auton {
    void setAutonRunType(int allianceColor, autonomousType autonType) {
        currentAutonType = autonType;
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
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Current Auton Type: %d", getAutonRunType());
    }

    autonomousType getAutonRunType() {
        return currentAutonType;
    }
    void runAutonomous() {
        switch (currentAutonType) {
            case redUp:
                break;
            case redDown:
                break;
            case blueUp:
                break;
            case blueDown:
                break;
            case autonSkill:
                break;
            case drivingSkill:
                break;
            case test:
                Brain.Screen.print("Running Test Auton");
                break;
        }
    }
}

namespace {
    void runAutonRedUp() {
        // Implement Red Up autonomous logic
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