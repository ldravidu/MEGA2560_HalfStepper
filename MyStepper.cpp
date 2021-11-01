#include "MyStepper.h"

// Pulses needed to execute steps ------- {X,Xb, Y,Yb}
const bool MyStepper::stepsArray[8][4] = {{1, 0, 0, 0},
                                          {1, 0, 1, 0},
                                          {0, 0, 1, 0},
                                          {0, 1, 1, 0},
                                          {0, 1, 0, 0},
                                          {0, 1, 0, 1},
                                          {0, 0, 0, 1},
                                          {1, 0, 0, 1}};

void MyStepper::rotate()
{
    megaPins::GPIO_DigitalWrite(stepsArray[currentStep % 8][0], pinX);
    megaPins::GPIO_DigitalWrite(stepsArray[currentStep % 8][1], pinX);
    megaPins::GPIO_DigitalWrite(stepsArray[currentStep % 8][2], pinX);
    megaPins::GPIO_DigitalWrite(stepsArray[currentStep % 8][3], pinX);
}

int MyStepper::angleToSteps(int angle)
{
    return angle / (360.0 / TotalSteps);
}

void MyStepper::incStepsAndAngles()
{
    ++(this->steps);
    this->angle = this->steps * (360.0 / TotalSteps);
}

MyStepper::MyStepper(const int pinX, const int pinXb, const int pinY, const int pinYb, const int TotalSteps)
    : pinX(pinX), pinXb(pinXb), pinY(pinY), pinYb(pinYb), TotalSteps(TotalSteps)
{
    megaPins X(pinX), Xb(pinXb), Y(pinY), Yb(pinYb);

    X.setPinMode(megaPins::GPIO_OUTPUT);
    Xb.setPinMode(megaPins::GPIO_OUTPUT);
    Y.setPinMode(megaPins::GPIO_OUTPUT);
    Yb.setPinMode(megaPins::GPIO_OUTPUT);

    X.GPIO_DigitalWrite(0);
    Xb.GPIO_DigitalWrite(0);
    Y.GPIO_DigitalWrite(0);
    Yb.GPIO_DigitalWrite(0);

    currentStep = 0;
    this->rotate();
    this->reset();
}

void MyStepper::setRpm(const int rpm)
{
    this->delay = (60 * 1000000) / (TotalSteps * rpm); // Delay is in microseconds
}

void MyStepper::rotateClockwise()
{
    ++currentStep;
    incStepsAndAngles();
    this->rotate();
}

void MyStepper::rotateAntiClockwise()
{
    --currentStep;
    incStepsAndAngles();
    this->rotate();
}

void MyStepper::rotateStepsClockwise(const int steps)
{
    for (int i = 0; i < steps; i++)
    {
        rotateClockwise();
        delayMicroseconds(this->delay);
    }
}

void MyStepper::rotateStepsAntiClockwise(const int steps)
{
    for (int i = 0; i < steps; i++)
    {
        rotateAntiClockwise();
        delayMicroseconds(this->delay);
    }
}

void MyStepper::rotateAngleClockwise(const int angle)
{
    this->rotateStepsClockwise(this->angleToSteps(angle));
}

void MyStepper::rotateAngleAntiClockwise(const int angle)
{
    this->rotateStepsAntiClockwise(this->angleToSteps(angle));
}

int MyStepper::getStepsRotated()
{
    return this->steps;
}

int MyStepper::getAngleRotated()
{
    return this->angle;
}

void MyStepper::reset()
{
    this->steps = 0;
    this->angle = 0;
}