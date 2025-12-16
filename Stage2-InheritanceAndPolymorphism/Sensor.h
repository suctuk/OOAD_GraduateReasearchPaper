#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    virtual void begin() = 0;
    virtual float readValue() = 0; 
    // Pure virtual function
    virtual ~Sensor() {}
};

#endif