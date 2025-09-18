#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
#include "Auton/preauton.h"
#include "main.h"

namespace {
    using namespace auton;
    using namespace autonFunctions;
    autonomousType currentAutonType = autonomousType::test;
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
        preauton::waitCalibrating();
        setRotation(54.0);
        driveDistanceTiles(-1.7, 90.0, 0.1, 0.9);
        LeftRightMotors.stop(brake);
        //turn to score pre-load
        turnToAngle(2, 0, 2.0, 0.7);
        LeftRightMotors.stop(brake);
        driveDistanceTiles(-0.26, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        //score pre-load
        intake3rdStage(1, 0);
        wait(0.8, sec);
        driveDistanceTiles(0.87, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        //turn to pick up center balls
        
        turnToAngle(-42, 0, 2.0, 0.7);
        LeftRightMotors.stop(brake);
        driveDistanceTiles(-1.57, 90.0, 0.1, 0.9);
        LeftRightMotors.stop(brake);
        //intake center balls
        intakeStore(1, 0);
        wait(0.3, sec);
        turnToAngle(-38, 0, 2.0, 0.7);
        //score center balls
        intake1stStage(1, 0.5);
        driveDistanceTiles(-0.6, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        wait(1.5, sec);
    }

    void RedLeft() {
        preauton::waitCalibrating();
        setRotation(-54.0);
        driveDistanceTiles(-1.6, 90.0, 0.1, 0.9);
        LeftRightMotors.stop(brake);
        turnToAngle(-2, 0, 2.0, 0.9);
        LeftRightMotors.stop(brake);
        driveDistanceTiles(-0.45, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        intake3rdStage(1, 0);
        wait(3, sec);
        driveDistanceTiles(0.8, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        turnToAngle(45, 0, 2.0, 1);
        LeftRightMotors.stop(brake);
        driveDistanceTiles(-1.4, 90.0, 0.1, 0.9);
        LeftRightMotors.stop(brake);
        intakeStore(1, 0);
        wait(3, sec);
        driveDistanceTiles(-1, 90.0, 0.1, 0.8);
        LeftRightMotors.stop(brake);
        intake2ndStage(1, 0);
        wait(2, sec);
    }

    void BlueRight() {
        preauton::waitCalibrating();
        intake2ndStage(1, 0);
        wait(2, sec);
        intake3rdStage(1, 0);
        wait(2, sec);
    }

    void BlueLeft() {
        preauton::waitCalibrating();
        intakeStore(1, 0);
        wait(5, sec);
    }

    void AutonSkill() {
        
    }

    void DrivingSkill() {
   
    }

    void Test() {
        preauton::waitCalibrating();
        driveAndTurnDistanceTiles(1, 90, 90, 100, 0, 0.1, 2.0);
    }
}