#include "Utilities/generalUtilities.h"

namespace genutil {
    double clamp (double value, double min, double max) {
        return fmax(fmin(value, max), min);
    }

    double pctToVolt(double pct) {
        return (pct * 12.0) / 100.0;
    }

    double voltToPct(double volt) {
        return (volt * 100.0) / 12.0;
    }

    double degToRad(double degrees) {
        return degrees* (M_PI / 180.0);
    }

    double radToDeg(double radians) {
        return radians * (180.0 / M_PI);
    }

    bool isWithin(double value, double target, double withinRange) {
        return fabs(value - target) <= withinRange;
    }

    int signum(double value) {
        return (value > 0) - (value < 0);
    }
}