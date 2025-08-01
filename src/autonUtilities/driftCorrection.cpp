#include "autonUtilities/driftCorrection.h";

DriftCorrection::DriftCorrection(inertial &sensor, double perClockwiseRevDrift, 
    double perCounterClockwiseRevDrift)
    : sensor(&sensor),
      perClockwiseRevDrift(perClockwiseRevDrift), 
      perCounterClockwiseRevDrift(perCounterClockwiseRevDrift), 
      lastAngle(0.0) {}

void DriftCorrection::setInertial() {
    lastAngle = sensor -> rotation();
}

void DriftCorrection::correctDrift() {
    double currentAngle = sensor -> rotation();
    double deltaRotation = currentAngle - lastAngle;
    double newAngle = currentAngle + deltaRotation / 360.0 * (deltaRotation > 0 ?
        perClockwiseRevDrift : perCounterClockwiseRevDrift);
    sensor -> setRotation(newAngle, deg);
    lastAngle = sensor -> rotation();
}