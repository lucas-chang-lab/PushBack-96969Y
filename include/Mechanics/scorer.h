#pragma once


namespace scorer {
    void runThread();

    void preauton();

    void setState(int, double = 0);

    void switchState();

    void control(int);

    bool canControl();
    
    extern bool filtering;
    extern int _taskState;
    extern double _taskDelay;
    extern bool locked;
    extern bool isSwitchedState;
    extern char filterColor; // 'r' = red, 'b' = blue,
    extern bool filter;
}