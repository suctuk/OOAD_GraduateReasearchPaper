#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Sensor.h"

class LightSensor : public Sensor {
    int pin;
public:
    LightSensor(int p) : pin(p) {}
    void begin() override;
    float readValue() override;
};

#endif
