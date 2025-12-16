#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

class TemperatureSensor : public Sensor {
    int pin;
public:
    TemperatureSensor(int p) : pin(p) {}
    void begin() override;
    float readValue() override;
};

#endif