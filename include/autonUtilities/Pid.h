#pragma once
#include "vex.h"

class PIDControl {
public:
    PIDControl(double kP = 0, double kI = 0, double kD = 0, double settleRange = 5, double settleMinFrameCount = 10);
    void setGains(double kP, double kI, double kD);
    void computeFromError(double error);
    void setIntegral(double integral);
    double getOutput(bool useP = true, bool useI = true, bool useD = true);
    bool isSettled();

private:
    double kP, kI, kD;
    double settleRange, settleMinFrameCount;
    double currentError, previousError, cumulativeError, deltaError;
    double settledFrames;
};