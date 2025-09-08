#pragma once
#include "main.h"

namespace auton {
    enum autonomousType {
        redRight, redLeft, 
        blueRight, blueLeft, 
        autonSkill, drivingSkill,
        test
    };
    // red -> 1, blue -> 2, nuetual -> 0
    void setAutonRunType(int allianceColor, autonomousType autonType);
    void showAutonRunType();
    autonomousType getAutonRunType();
    bool isUserRunningAuton();
    void runAutonomous();
    void autonSkillsIntro();
}

