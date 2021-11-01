#ifndef MY_STEPPER_H
#define MY_STEPPER_H

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef MEGA_PINS_H
#include "megaPins.h"
#endif

class MyStepper
{
private:
    int pinX;
    int pinXb;
    int pinY;
    int pinYb;
    int delay;
    int steps;
    int angle;
    int currentStep;
    const int TotalSteps;
    static const bool stepsArray[8][4];

    void rotate();
    int angleToSteps(int angle);
    void incStepsAndAngles();

public:
    MyStepper(const int pinX, const int pinXb, const int pinY, const int pinYb, const int TotalSteps = 400);
    void setRpm(const int rpm);
    void rotateClockwise();
    void rotateAntiClockwise();
    void rotateStepsClockwise(const int steps);
    void rotateStepsAntiClockwise(const int steps);
    void rotateAngleClockwise(const int angle);
    void rotateAngleAntiClockwise(const int angle);
    int getStepsRotated();
    int getAngleRotated();
    void reset();
};

#endif