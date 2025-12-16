/*
 * LEDObject.h
 * 
 * Header file for the LEDObject class.
 * Demonstrates fundamental OOP concepts: encapsulation and method invocation.
 * 
 * This class encapsulates the behavior and state of an LED, providing a
 * clean interface for controlling LED hardware while hiding internal details.
 */

#ifndef LEDOBJECT_H
#define LEDOBJECT_H

class LEDObject {
  private:
    // ENCAPSULATION: Private data members
    // These internal state variables cannot be accessed directly from outside the class
    // This protects the object's integrity and enforces controlled access
    int ledPin;        // Hardware pin number connected to the LED
    bool isOn;         // Current state of the LED (true = on, false = off)

  public:
    // CONSTRUCTOR: Initializes the LED object with a specific pin
    // Constructor is called automatically when object is created
    LEDObject(int pin);
    
    // PUBLIC INTERFACE: Methods that provide controlled access to LED functionality
    // These methods demonstrate METHOD INVOCATION and maintain encapsulation
    
    void turnOn();     // Turn the LED on (set HIGH)
    void turnOff();    // Turn the LED off (set LOW)
    void toggle();     // Toggle the LED state (on->off or off->on)
    void blink(int duration); // Blink the LED once with specified duration
    
    // ACCESSOR METHOD (Getter): Provides read-only access to private state
    // This maintains encapsulation while allowing controlled state inspection
    bool getState();   // Returns true if LED is on, false if off
    
    // Additional query method
    int getPin();      // Returns the pin number this LED is connected to
};

/*
 * Key OOP Concepts Demonstrated:
 * 
 * 1. ENCAPSULATION:
 *    - Private data members (ledPin, isOn) hide internal state
 *    - Public methods provide controlled access
 *    - Users cannot directly manipulate internal state
 * 
 * 2. ABSTRACTION:
 *    - Users interact with LED through simple methods (turnOn, turnOff)
 *    - Hardware details (digitalWrite, pinMode) are hidden
 *    - Interface is intuitive and hardware-independent
 * 
 * 3. INFORMATION HIDING:
 *    - Implementation details are hidden in .cpp file
 *    - Only public interface is exposed in header
 *    - Changes to implementation won't affect users of the class
 */

#endif