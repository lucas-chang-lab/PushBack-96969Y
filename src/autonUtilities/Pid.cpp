#include "autonUtilities/Pid.h"
#include <cmath>

PIDControl::PIDControl(double kP, double kI, double kD, double settleRange, double settleFrameCount)
    : kP(kP), kI(kI), kD(kD), settleRange(fabs(settleRange)), settleMinFrameCount(settleFrameCount),
      currentError(0), previousError(0), cumulativeError(0), deltaError(0),
      settledFrameCount(0) {}

void PIDControl::computeFromError(double error) {
    deltaError = error - previousError;
    currentError = error;
    previousError = currentError;
    bool isCrossZero = (currentError * previousError < 0);
    if (isCrossZero) {
        cumulativeError = 0;
    } else {
        cumulativeError += currentError;
    }
}

void PIDControl::setError(double errorI) {
    cumulativeError = errorI;
}

double PIDControl::getOutput(bool useP, bool useI, bool useD) {
    double valueP = useP ? kP * currentError : 0;
    double valueI = useI ? kI * cumulativeError : 0;
    double valueD = useD ? kD * deltaError : 0;
    return valueP + valueI + valueD;
}

bool PIDControl::isSettled() {
    if (fabs(currentError) < settleRange && settledFrameCount >= settleMinFrameCount) {
        return true;
    } else {
        return false;
    }
}