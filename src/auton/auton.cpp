#include "Auton/auton.h"
#include "Auton/autonFunctions.h"
#include "Auton/preauton.h"
#include "AutonUtilities/odometry.h"
#include "Mechanics/scorer.h"
#include "Graphic/autonSelector.h"
#include "main.h"
#include "Mechanics/scorer.h"

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
        if (autonSelector::isAutonSelected()) {
            currentAutonType = autonSelector::getSelectedAuton();   // Override with selected auton
        }
        printf("Running Auton Type: %d\n", currentAutonType);
        preauton::waitCalibrating();    // Ensure sensors are calibrated before starting auton
        timer benchmarkTimer;
        benchmarkTimer.reset();
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
        printf("Auton Time: %.2f seconds \n", benchmarkTimer.value());
    }
}

namespace {
    void RedRight() {
        //odometry::setValues(2,0,-7);
        setRotation(14.5);
        intakeStore(1, 0.1);
        setMatchLoader(1, 0.8);
        driveDistanceTiles(1.24, 36.0, 0.1, 1.5);
        setMatchLoader(0, 0.2);
        turnToAngle(-56.5, 0, 1.0, 0.8);
        intake1stStage(1, 1);
        driveDistanceTiles(0.65, 50.0, 0.1, 1.2);
        wait(0.7, sec);
        intake1stStage(0, 0);
        driveDistanceTiles(-1.99, 50.0, 0.1, 1.6);
        turnToAngle(-188, 0, 1.0, 0.8);
        //driveDistanceTiles(0.52, 90.0, 0.1, 1.0);
        //LeftRightMotors.spin(reverse, 12, volt);
        //wait(0.7, sec);
        setMatchLoader(1, 0.0);
        wait(100, msec);
        intakeStore(1, 0);
        driveDistanceTiles(0.71, 60.0, 0.1, 1.0);
        wait(1.5, sec);
        setMatchLoader(0, 0.2);
        intakeStore(0, 0);
        intake3rdStage(1, 1.4);
        driveDistanceTiles(-1.22, 50.0, 0.1, 2.0);
        wait(1.5, sec);
        driveDistanceTiles(0.3, 50.0, 0.1, 1.0);
        LeftRightMotors.spin(forward, 12, volt);
    }

    void RedLeft() {
        //odometry::setValues(2,0,-7);
        setRotation(-14.5);
        intakeStore(1, 0.1);
        setMatchLoader(1, 0.8);
        driveDistanceTiles(1.24, 36.0, 0.1, 1.5);
        setMatchLoader(0, 0.2);
        turnToAngle(-141, 0, 1.0, 0.8);
        intake2ndStage(1, 1);
        driveDistanceTiles(-0.65, 50.0, 0.1, 1.2);
        wait(0.3, sec);
        intake2ndStage(0, 0);
        driveDistanceTiles(1.98, 50.0, 0.1, 1.6);
        turnToAngle(-175, 0, 1.0, 0.8);
        //driveDistanceTiles(0.52, 90.0, 0.1, 1.0);
        //LeftRightMotors.spin(reverse, 12, volt);
        //wait(0.7, sec);
        setMatchLoader(1, 0.0);
        wait(100, msec);
        intakeStore(1, 0);
        driveDistanceTiles(0.9, 60.0, 0.1, 1.4);
        wait(1.5, sec);
        setMatchLoader(0, 0.2);
        intakeStore(0, 0);
        intake3rdStage(1, 1.4);
        driveDistanceTiles(-1.22, 50.0, 0.1, 2.0);
        wait(1.5, sec);
        driveDistanceTiles(0.3, 50.0, 0.1, 1.0);
        LeftRightMotors.spin(forward, 12, volt);
    }

    void BlueRight() {
         setRotation(14.5);
        intakeStore(1, 0.1);
        setMatchLoader(1, 0.8);
        driveDistanceTiles(1.24, 36.0, 0.1, 1.5);
        setMatchLoader(0, 0.2);
        turnToAngle(-56.5, 0, 1.0, 0.8);
        intake1stStage(1, 1);
        driveDistanceTiles(0.65, 50.0, 0.1, 1.2);
        wait(0.7, sec);
        intake1stStage(0, 0);
        driveDistanceTiles(-1.99, 50.0, 0.1, 1.6);
        turnToAngle(-188, 0, 1.0, 0.8);
        //driveDistanceTiles(0.52, 90.0, 0.1, 1.0);
        //LeftRightMotors.spin(reverse, 12, volt);
        //wait(0.7, sec);
        setMatchLoader(1, 0.0);
        wait(100, msec);
        intakeStore(1, 0);
        driveDistanceTiles(0.71, 60.0, 0.1, 1.0);
        wait(1.5, sec);
        setMatchLoader(0, 0.2);
        intakeStore(0, 0);
        intake3rdStage(1, 1.4);
        driveDistanceTiles(-1.22, 50.0, 0.1, 2.0);
        wait(1.5, sec);
        driveDistanceTiles(0.3, 50.0, 0.1, 1.0);
        LeftRightMotors.spin(forward, 12, volt);
    }

    void BlueLeft() {
        preauton::waitCalibrating();
        //odometry::setValues(2,0,-7);
        setRotation(-14.5);
        intakeStore(1, 0.1);
        setMatchLoader(1, 0.8);
        driveDistanceTiles(1.24, 36.0, 0.1, 1.5);
        setMatchLoader(0, 0.2);
        turnToAngle(-141, 0, 1.0, 0.8);
        intake2ndStage(1, 1);
        driveDistanceTiles(-0.65, 50.0, 0.1, 1.2);
        wait(0.3, sec);
        intake2ndStage(0, 0);
        driveDistanceTiles(1.98, 50.0, 0.1, 1.6);
        turnToAngle(-175, 0, 1.0, 0.8);
        //driveDistanceTiles(0.52, 90.0, 0.1, 1.0);
        //LeftRightMotors.spin(reverse, 12, volt);
        //wait(0.7, sec);
        setMatchLoader(1, 0.0);
        wait(100, msec);
        intakeStore(1, 0);
        driveDistanceTiles(0.9, 60.0, 0.1, 1.4);
        wait(1.5, sec);
        setMatchLoader(0, 0.2);
        intakeStore(0, 0);
        intake3rdStage(1, 1.4);
        driveDistanceTiles(-1.22, 50.0, 0.1, 2.0);
        wait(1.5, sec);
        driveDistanceTiles(0.3, 50.0, 0.1, 1.0);
        LeftRightMotors.spin(forward, 12, volt);
    }

    void AutonSkill() {
        
    }

    void DrivingSkill() {
   
    }

    void Test() {
    }
}