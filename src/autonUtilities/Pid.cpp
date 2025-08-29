#include "AutonUtilities/Pid.h"
#include <cmath>

PIDControl::PIDControl(double kP, double kI, double kD, double settleRange, double settleFrameCount)
    : kP(kP), kI(kI), kD(kD), settleRange(fabs(settleRange)), settleMinFrameCount(settleFrameCount),
      currentError(2e17), previousError(2e17), cumulativeError(0), deltaError(0),
      settledFrames(0) {}

void PIDControl::computeFromError(double error) {
    if (previousError > 1e17) {
        previousError = error;
    } else {
        previousError = currentError;
    }

    currentError = error;
    bool isCrossZero = (currentError * previousError < 0);
    if (isCrossZero) {
        cumulativeError = 0;
    } else {
        cumulativeError += currentError;
    }
    deltaError = currentError - previousError;

    if (fabs(error) < settleRange) {
        settledFrames++;
        settledFrames = fmin(settledFrames, settleMinFrameCount + 1);
    } else {
        settledFrames = 0;
    }
}

void PIDControl::setIntegral(double integral) {
    cumulativeError = integral;
}

double PIDControl::getOutput(bool useP, bool useI, bool useD) {
    double valueP = useP ? kP * currentError : 0;
    double valueI = useI ? kI * cumulativeError : 0;
    double valueD = useD ? kD * deltaError : 0;
    return valueP + valueI + valueD;
}

bool PIDControl::isSettled() {
    if (fabs(currentError) < settleRange && settledFrames >= settleMinFrameCount) {
        return true;
    } else {
        return false;
    }
}