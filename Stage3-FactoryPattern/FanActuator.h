/*
 * FanActuator.h
 * 
 * Concrete implementation of the Actuator interface for cooling fans.
 * Demonstrates how easily new actuator types can be added to the factory.
 * 
 * Hardware: DC fan controlled via PWM pin (similar to motor but simpler)
 */

#ifndef FANACTUATOR_H
#define FANACTUATOR_H

#include "Actuator.h"

class FanActuator : public Actuator {
  private:
    int pin;           // PWM pin for fan speed control
    int currentSpeed;  // Current fan speed (0-255)
    bool isActive;     // Whether fan is currently running
    
  public:
    // Constructor
    FanActuator(int fanPin);
    
    // Override pure virtual functions from Actuator
    void activate() override;
    void deactivate() override;
    void setValue(int value) override;
    int getValue() override;
    String getType() override;
    
    // Fan-specific methods
    void setSpeed(int speed);
};

#endif
