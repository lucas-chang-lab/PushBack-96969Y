#pragma once


namespace backIntake {
    void runThread();

    void preauton();

    void setState(int, double = 0, double = 12.0);

    void switchState();

    void control(int, double = 12.0);

    bool canControl();
    
    extern int _taskState;
    extern double _taskDelay;
}