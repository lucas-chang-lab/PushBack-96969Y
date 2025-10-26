#include "Auton/auton.h"
#include "Graphic/autonSelector.h"
#include "Mechanics/scorer.h"

namespace {
    auton::autonomousType selectedAuton = auton::autonomousType::test;
    bool autonSelected = false;
}

namespace autonSelector {
    using namespace auton;
    void drawButton(int x, int y, int w, int h, color fillColor, const char *label, bool selected) {
        Brain.Screen.setFillColor(fillColor);
        Brain.Screen.drawRectangle(x, y, w, h);

        Brain.Screen.setFont(monoL);
        Brain.Screen.setPenColor(white);
        Brain.Screen.printAt(x + 20, y + h/2, label);

        if (selected) {
            Brain.Screen.setFillColor(yellow);
            Brain.Screen.setPenColor(black);
            Brain.Screen.drawRectangle(x, y, w, h);
            Brain.Screen.printAt(x + 20, y + h/2, label);
        }
    }

    void drawAutonSelector() {
        Brain.Screen.clearScreen();

        drawButton(0, 0, 240, 120, blue, "Blue Left", selectedAuton == autonomousType::blueLeft);
        drawButton(240, 0, 240, 120, blue, "Blue Right", selectedAuton == autonomousType::blueRight);
        drawButton(0, 120, 240, 120, red, "Red Left", selectedAuton == autonomousType::redLeft);
        drawButton(240, 120, 240, 120, red, "Red Right", selectedAuton == autonomousType::redRight);
    }

    void selectAuton() {
        int x = Brain.Screen.xPosition();
        int y = Brain.Screen.yPosition();

        autonSelected = true;
        if (y < 120 && x < 240) {
            selectedAuton = autonomousType::blueLeft;
            scorer::filterColor = 'r';
        } else if (y < 120 && x >= 240) {
            selectedAuton = autonomousType::blueRight;
            scorer::filterColor = 'r';
        } else if (y >= 120 && x < 240) {
            selectedAuton = autonomousType::redLeft;
            scorer::filterColor = 'b';
        } else if (y >= 120 && x >= 240) {
            selectedAuton = autonomousType::redRight;
            scorer::filterColor = 'b';
        }

        drawAutonSelector();
    }

    void pre_auton(void) {
        drawAutonSelector();

        while(!Competition.isAutonomous()) {
            if (Brain.Screen.pressing()) {
                selectAuton();
                while(Brain.Screen.pressing()) {
                    wait(10, msec);   // debounce
                }
            }
            wait(100, msec);
        }
    }

    auton::autonomousType getSelectedAuton() {
        return selectedAuton;
    }

    bool isAutonSelected() {
        return autonSelected;
    }
}