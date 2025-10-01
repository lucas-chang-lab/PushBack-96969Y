#pragma once
#include <cmath>

namespace genutil {
    double clamp(double value, double min, double max);
    double pctToVolt(double pct);
    double voltToPct(double volt);
    double degToRad(double degrees);
    double radToDeg(double radians);
    bool isWithin(double value, double target, double withinRange);
    int signum(double value);

    double wrapAngle(double angle);

    void distanceTesting();
    void odometryTesting();
}