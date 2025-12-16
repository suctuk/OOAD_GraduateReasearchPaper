/*
 * MotorActuator.h
 * 
 * Concrete implementation of the Actuator interface for DC motors.
 * Demonstrates inheritance and polymorphism in the Factory Pattern.
 * 
 * Hardware: DC motor controlled via PWM pin (and optional direction pin)
 * For Arduino Uno, use any PWM pin (3, 5, 6, 9, 10, 11)
 */

#ifndef MOTORACTUATOR_H
#define MOTORACTUATOR_H

#include "Actuator.h"

class MotorActuator : public Actuator {
  private:
    int speedPin;      // PWM pin for motor speed control
    int directionPin;  // Optional direction pin (-1 if not used)
    int currentSpeed;  // Current motor speed (0-255)
    bool isActive;     // Whether motor is currently active
    
  public:
    // Constructor with speed pin only (simple DC motor)
    MotorActuator(int sPin);
    
    // Constructor with speed and direction pins (motor driver like L298N)
    MotorActuator(int sPin, int dPin);
    
    // Override pure virtual functions from Actuator
    void activate() override;
    void deactivate() override;
    void setValue(int value) override;
    int getValue() override;
    String getType() override;
    
    // Motor-specific methods
    void setDirection(bool forward);
};

#endif