#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "Sensor.h"

class UltrasonicSensor : public Sensor {
    int trigPin;
    int echoPin;
public:
    UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {}
    void begin() override;
    float readValue() override;
};

#endif
