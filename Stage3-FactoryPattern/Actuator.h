/*
 * Actuator.h
 * 
 * Abstract base class for all actuator types.
 * Demonstrates polymorphism and interface design in the Factory Pattern.
 * 
 * This class defines the contract that all actuators must follow,
 * enabling the factory to create different actuator types that can
 * be used interchangeably through a common interface.
 */

#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
  public:
    // Pure virtual functions - must be implemented by derived classes
    
    // Initialize and start the actuator
    virtual void activate() = 0;
    
    // Stop and cleanup the actuator
    virtual void deactivate() = 0;
    
    // Set the actuator value (speed, angle, power, etc.)
    // Parameter meaning depends on actuator type
    virtual void setValue(int value) = 0;
    
    // Get the current actuator value
    virtual int getValue() = 0;
    
    // Get the type name of this actuator (for debugging)
    virtual String getType() = 0;
    
    // Virtual destructor ensures proper cleanup of derived classes
    virtual ~Actuator() {}
};

/*
 * Design Pattern: Abstract Factory Interface
 * 
 * This abstract class serves as the product interface in the Factory Pattern.
 * All concrete actuators (Motor, Servo, Fan) inherit from this class and
 * provide their own implementations of these methods.
 * 
 * Benefits:
 * - Client code can work with any actuator type through this interface
 * - New actuator types can be added without changing client code
 * - Promotes loose coupling between creation and usage
 */

#endif