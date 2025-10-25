#pragma once
#include "vex.h"
#include "main.h"
#include "Auton/auton.h"

namespace autonSelector {
    void drawButton(int x, int y, int w, int h, color fillColor, const char *label, bool selected);
    void drawAutonSelector();
    void selectAuton();
    void pre_auton(void);

    auton::autonomousType getSelectedAuton();
    bool isAutonSelected();
}