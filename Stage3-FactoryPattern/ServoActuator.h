/*
 * ServoActuator.h
 * 
 * Concrete implementation of the Actuator interface for servo motors.
 * Demonstrates inheritance and polymorphism in the Factory Pattern.
 * 
 * Hardware: Standard hobby servo motor (0-180 degrees)
 * For Arduino Uno, servos can be connected to any digital pin
 */

#ifndef SERVOACTUATOR_H
#define SERVOACTUATOR_H

#include "Actuator.h"
#include <Servo.h>  // Arduino Servo library

class ServoActuator : public Actuator {
  private:
    Servo servo;        // Servo library object
    int pin;            // Pin connected to servo
    int currentAngle;   // Current servo angle (0-180)
    bool isActive;      // Whether servo is currently attached
    
  public:
    // Constructor
    ServoActuator(int servoPin);
    
    // Override pure virtual functions from Actuator
    void activate() override;
    void deactivate() override;
    void setValue(int value) override;
    int getValue() override;
    String getType() override;
    
    // Servo-specific methods
    void setAngle(int angle);
    void sweep(int startAngle, int endAngle, int delayMs);
};

#endif