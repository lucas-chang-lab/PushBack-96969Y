#pragma once
#include "vex.h"

class Pid {
public:
    Pid(double kP = 0, double kI = 0, double kD = 0, double settleRange = 5, double settleFrameCount = 10);
    void computeFromError(double error);
    void setError(double errorI);
    double getOutput(bool useP = true, bool useI = true, bool useD = true);
    bool isSettled();

private:
    double kP, kI, kD;
    double currentError, previousError, cumulativeError, deltaError;
    double settleRange, settleMinFrameCount;
    double settledFrameCount;
};