#pragma once
#include "main.h"

class DriftCorrection {
public:
    DriftCorrection(inertial &sensor, double perClockwiseRevDrift = 0.0, 
        double perCounterClockwiseRevDrift = 0.0);
    void setInertial();
    void correctDrift();

private:
    inertial *sensor;
    double perClockwiseRevDrift, perCounterClockwiseRevDrift;
    double lastAngle;
};