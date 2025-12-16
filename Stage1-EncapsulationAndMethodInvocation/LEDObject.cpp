/*
 * LEDObject.cpp
 * 
 * Implementation file for the LEDObject class.
 * Contains the actual code that executes when methods are called.
 * This separation of interface (.h) from implementation (.cpp) is a key
 * principle of encapsulation and modular programming.
 */

#include "LEDObject.h"
#include <Arduino.h>

/*
 * CONSTRUCTOR: LEDObject(int pin)
 * 
 * Purpose: Initialize a new LED object
 * Parameters: pin - the Arduino digital pin number connected to the LED
 * 
 * This constructor:
 * 1. Stores the pin number in the private member variable
 * 2. Initializes the state to off (false)
 * 3. Configures the hardware pin as OUTPUT
 * 4. Ensures the LED starts in the OFF state
 * 
 * Called automatically when creating an LEDObject: LEDObject led(13);
 */
LEDObject::LEDObject(int pin) {
  ledPin = pin;           // Store pin number
  isOn = false;           // Initialize state to off
  pinMode(ledPin, OUTPUT); // Configure pin as output
  digitalWrite(ledPin, LOW); // Ensure LED starts off
}

/*
 * METHOD: turnOn()
 * 
 * Purpose: Turn the LED on
 * 
 * This method demonstrates encapsulation by:
 * 1. Performing the hardware operation (digitalWrite HIGH)
 * 2. Updating the internal state (isOn = true)
 * 3. Maintaining consistency between hardware and software state
 * 
 * Users don't need to know about digitalWrite or pin modes;
 * they just call turnOn() and the LED lights up.
 */
void LEDObject::turnOn() {
  digitalWrite(ledPin, HIGH);  // Hardware operation
  isOn = true;                 // Update internal state
}

/*
 * METHOD: turnOff()
 * 
 * Purpose: Turn the LED off
 * 
 * Mirrors turnOn() by setting hardware LOW and updating state to false.
 * Maintains the encapsulation of both hardware control and state management.
 */
void LEDObject::turnOff() {
  digitalWrite(ledPin, LOW);   // Hardware operation
  isOn = false;                // Update internal state
}

/*
 * METHOD: toggle()
 * 
 * Purpose: Switch the LED to the opposite state (on->off or off->on)
 * 
 * This method demonstrates:
 * 1. Reading private state (isOn)
 * 2. Making decisions based on state
 * 3. Using existing methods (turnOn/turnOff) for consistency
 * 
 * This is an example of building higher-level functionality
 * on top of basic operations while maintaining encapsulation.
 */
void LEDObject::toggle() {
  if (isOn) {
    turnOff();  // If currently on, turn off
  } else {
    turnOn();   // If currently off, turn on
  }
}

/*
 * METHOD: blink(int duration)
 * 
 * Purpose: Blink the LED once with specified duration
 * Parameters: duration - how long to keep LED on (in milliseconds)
 * 
 * This method demonstrates:
 * 1. Method parameters for flexible behavior
 * 2. Combining multiple operations (on, delay, off)
 * 3. Preserving the original state after the blink
 * 
 * Example: led.blink(500); // Blink for half a second
 */
void LEDObject::blink(int duration) {
  bool originalState = isOn;  // Remember original state
  
  turnOn();                   // Turn on
  delay(duration);            // Wait
  turnOff();                  // Turn off
  
  // Restore original state if it was on before
  if (originalState) {
    turnOn();
  }
}

/*
 * METHOD: getState()
 * 
 * Purpose: Return the current state of the LED
 * Returns: true if LED is on, false if off
 * 
 * This is an ACCESSOR or GETTER method.
 * It provides read-only access to private data, demonstrating that
 * encapsulation doesn't mean "no access" - it means "controlled access".
 * 
 * Users can check the state without being able to directly modify it,
 * ensuring that state changes always go through proper methods that
 * keep hardware and software synchronized.
 */
bool LEDObject::getState() {
  return isOn;
}

/*
 * METHOD: getPin()
 * 
 * Purpose: Return the pin number this LED is connected to
 * Returns: The Arduino pin number
 * 
 * Another accessor method providing read-only access to private data.
 * Useful for debugging or when you need to know which pin is in use.
 */
int LEDObject::getPin() {
  return ledPin;
}

/*
 * Implementation Notes:
 * 
 * 1. All methods maintain the relationship between software state (isOn)
 *    and hardware state (HIGH/LOW on pin).
 * 
 * 2. Private variables cannot be accessed from outside the class,
 *    enforcing the use of these methods.
 * 
 * 3. Changes to implementation (e.g., using PWM for brightness) can be
 *    made here without affecting code that uses the class.
 * 
 * 4. Each method has a single, clear responsibility (Single Responsibility
 *    Principle from SOLID).
 */