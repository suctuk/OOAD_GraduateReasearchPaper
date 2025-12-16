/*
 * ActuatorFactory.h
 * 
 * Factory class for creating different types of actuators.
 * Implements the Factory Design Pattern.
 * 
 * This class demonstrates the key benefits of the Factory Pattern:
 * 1. Centralized object creation
 * 2. Loose coupling between creation and usage
 * 3. Easy to add new actuator types without changing client code
 * 4. Encapsulates the complexity of choosing and constructing objects
 */

#ifndef ACTUATORFACTORY_H
#define ACTUATORFACTORY_H

#include "Actuator.h"
#include "MotorActuator.h"
#include "ServoActuator.h"
#include "FanActuator.h"

class ActuatorFactory {
  public:
    /*
     * Create an actuator based on type string
     * 
     * Parameters:
     *   type - String identifier: "motor", "servo", or "fan"
     *   pin - Primary pin number for the actuator
     *   pin2 - Optional secondary pin (e.g., direction pin for motor)
     * 
     * Returns:
     *   Pointer to Actuator base class (polymorphism!)
     *   Returns nullptr if type is unrecognized
     * 
     * DESIGN PATTERN: Factory Method
     * The caller doesn't need to know which concrete class to instantiate.
     * The factory handles all the details of object creation.
     */
    static Actuator* createActuator(const String& type, int pin, int pin2 = -1) {
      // Convert to lowercase for case-insensitive comparison
      String lowerType = type;
      lowerType.toLowerCase();
      
      if (lowerType == "motor") {
        if (pin2 != -1) {
          // Motor with direction control
          return new MotorActuator(pin, pin2);
        } else {
          // Simple motor (speed only)
          return new MotorActuator(pin);
        }
      }
      else if (lowerType == "servo") {
        return new ServoActuator(pin);
      }
      else if (lowerType == "fan") {
        return new FanActuator(pin);
      }
      
      // Unknown type
      return nullptr;
    }
    
    /*
     * Overloaded factory method for backward compatibility
     * Uses default pins for Arduino Uno testing
     */
    static Actuator* createActuator(const String& type) {
      String lowerType = type;
      lowerType.toLowerCase();
      
      if (lowerType == "motor") {
        return new MotorActuator(5);  // Default to pin 5 (PWM)
      }
      else if (lowerType == "servo") {
        return new ServoActuator(9);  // Default to pin 9
      }
      else if (lowerType == "fan") {
        return new FanActuator(6);    // Default to pin 6 (PWM)
      }
      
      return nullptr;
    }
};

/*
 * DESIGN PATTERN EXPLANATION: Factory Pattern
 * 
 * Problem:
 * - Client code needs to create different types of actuators
 * - Direct instantiation (new MotorActuator(), new ServoActuator()) 
 *   creates tight coupling
 * - Adding new actuator types requires changing client code
 * 
 * Solution:
 * - Factory class handles object creation
 * - Client uses factory method instead of 'new'
 * - Returns base class pointer (Actuator*) for polymorphism
 * - New types added by extending factory, not changing clients
 * 
 * Benefits for Hardware Projects:
 * - Easy to swap hardware components (motor ↔ servo)
 * - Configuration-driven actuator selection
 * - Testable: can create mock actuators for testing
 * - Maintainable: centralized creation logic
 * 
 * Open-Closed Principle:
 * - Open for extension: Add new actuator types by creating new classes
 * - Closed for modification: Don't need to change existing client code
 */

#endif