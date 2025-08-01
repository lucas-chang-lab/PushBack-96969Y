#include "Utilities/fieldInfo.h"
#include "auton/autonValues.h"


namespace autonvals {
    const double defaultMoveTilesErrorRange = 0.065; 
    const double defaultMoveWithInchesErrorRange = defaultMoveTilesErrorRange * field::tileLengthIn;
    const double defaultTurnAngleErrorRange = 5.0; 
}