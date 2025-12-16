/*
 * Stage3.ino
 * 
 * Stage 3: Demonstrating the Factory Design Pattern
 * 
 * This Arduino sketch demonstrates advanced OOP concepts through the Factory Pattern:
 * - FACTORY PATTERN: Centralized object creation
 * - POLYMORPHISM: Using base class pointers for different actuator types
 * - LOOSE COUPLING: Separating object creation from usage
 * - OPEN-CLOSED PRINCIPLE: Easy to extend with new actuator types
 * 
 * Hardware Setup for Arduino Uno:
 * Option 1 - Motor only:
 *   - DC Motor connected to pin 5 (PWM) via motor driver
 * 
 * Option 2 - Servo only:
 *   - Servo motor connected to pin 9
 *   - Servo power: 5V and GND
 * 
 * Option 3 - Fan only:
 *   - DC Fan connected to pin 6 (PWM) via transistor/driver
 * 
 * Option 4 - Multiple actuators (requires external power):
 *   - Motor on pin 5, Servo on pin 9, Fan on pin 6
 * 
 * Learning Objectives:
 * 1. Understand how factories centralize and simplify object creation
 * 2. See polymorphism in action with different actuator types
 * 3. Experience the benefits of loose coupling and extensibility
 * 4. Learn how design patterns solve real-world problems
 */

#include "ActuatorFactory.h"

// Global actuator pointer - demonstrates polymorphism
// This single pointer can reference any type of actuator
Actuator* currentActuator = nullptr;

// Configuration: Change this to test different actuators
// Options: "motor", "servo", "fan"
String actuatorType = "servo";  // Default to servo for easy testing

void setup() {
  // Initialize serial for debugging and demonstration
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("========================================");
  Serial.println("Stage 3: Factory Design Pattern");
  Serial.println("========================================\n");
  
  // Run comprehensive demonstration
  demonstrateFactoryPattern();
  
  Serial.println("\n========================================");
  Serial.println("Interactive Mode Starting");
  Serial.println("========================================");
  Serial.println("Commands:");
  Serial.println("  1 - Create Motor");
  Serial.println("  2 - Create Servo");
  Serial.println("  3 - Create Fan");
  Serial.println("  a - Activate current actuator");
  Serial.println("  d - Deactivate current actuator");
  Serial.println("  + - Increase value");
  Serial.println("  - - Decrease value");
  Serial.println("  s - Show status");
  Serial.println("========================================\n");
}

void loop() {
  // Interactive control via Serial Monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    handleSerialCommand(command);
  }
  
  delay(100);  // Small delay for stability
}

/*
 * DEMONSTRATION FUNCTION
 * Shows the power of the Factory Pattern with multiple examples
 */
void demonstrateFactoryPattern() {
  Serial.println("--- Demonstration 1: Basic Factory Usage ---\n");
  
  // FACTORY PATTERN IN ACTION:
  // We don't use 'new MotorActuator()' or 'new ServoActuator()'
  // Instead, we ask the factory to create the appropriate object
  
  Serial.println("Creating a Motor actuator using factory...");
  Actuator* motor = ActuatorFactory::createActuator("motor", 5);
  
  if (motor != nullptr) {
    Serial.print("Created: ");
    Serial.println(motor->getType());
    motor->activate();
    Serial.println("Motor activated");
    
    Serial.println("Setting motor speed to 150...");
    motor->setValue(150);
    delay(2000);
    
    motor->deactivate();
    Serial.println("Motor deactivated\n");
    delete motor;  // Clean up
  }
  
  delay(1000);
  
  Serial.println("--- Demonstration 2: Polymorphic Behavior ---\n");
  
  // Create a servo using the same factory method
  Serial.println("Creating a Servo actuator using factory...");
  Actuator* servo = ActuatorFactory::createActuator("servo", 9);
  
  if (servo != nullptr) {
    Serial.print("Created: ");
    Serial.println(servo->getType());
    servo->activate();
    Serial.println("Servo activated");
    
    // Same method call (setValue), different behavior!
    Serial.println("Setting servo to 0 degrees...");
    servo->setValue(0);
    delay(1000);
    
    Serial.println("Setting servo to 90 degrees...");
    servo->setValue(90);
    delay(1000);
    
    Serial.println("Setting servo to 180 degrees...");
    servo->setValue(180);
    delay(1000);
    
    servo->deactivate();
    Serial.println("Servo deactivated\n");
    delete servo;
  }
  
  delay(1000);
  
  Serial.println("--- Demonstration 3: Easy Substitution ---\n");
  Serial.println("The factory makes it easy to swap actuator types!");
  Serial.println("Same code works with different hardware:\n");
  
  // Array of different actuator types
  String types[] = {"motor", "servo", "fan"};
  
  for (int i = 0; i < 3; i++) {
    Serial.print("Creating: ");
    Serial.println(types[i]);
    
    // Same factory call, different results!
    Actuator* actuator = ActuatorFactory::createActuator(types[i]);
    
    if (actuator != nullptr) {
      Serial.print("Type: ");
      Serial.println(actuator->getType());
      
      actuator->activate();
      actuator->setValue(100);
      delay(1000);
      actuator->deactivate();
      
      delete actuator;
      Serial.println();
    }
  }
  
  Serial.println("--- Demonstration 4: Error Handling ---\n");
  
  Serial.println("Attempting to create unknown actuator type...");
  Actuator* unknown = ActuatorFactory::createActuator("laser");
  
  if (unknown == nullptr) {
    Serial.println("Factory returned nullptr - type not recognized");
    Serial.println("This shows proper error handling!\n");
  }
  
  delay(1000);
  
  // Create the default actuator for interactive mode
  Serial.println("Creating default actuator for interactive mode...");
  currentActuator = ActuatorFactory::createActuator(actuatorType);
  
  if (currentActuator != nullptr) {
    Serial.print("Created: ");
    Serial.println(currentActuator->getType());
    currentActuator->activate();
    Serial.println();
  }
}

/*
 * INTERACTIVE CONTROL HANDLER
 * Demonstrates runtime control of polymorphic objects
 */
void handleSerialCommand(char command) {
  switch (command) {
    case '1':
      Serial.println("\n> Creating Motor...");
      if (currentActuator != nullptr) {
        currentActuator->deactivate();
        delete currentActuator;
      }
      currentActuator = ActuatorFactory::createActuator("motor", 5);
      if (currentActuator != nullptr) {
        Serial.println("Motor created and ready");
      }
      break;
      
    case '2':
      Serial.println("\n> Creating Servo...");
      if (currentActuator != nullptr) {
        currentActuator->deactivate();
        delete currentActuator;
      }
      currentActuator = ActuatorFactory::createActuator("servo", 9);
      if (currentActuator != nullptr) {
        Serial.println("Servo created and ready");
      }
      break;
      
    case '3':
      Serial.println("\n> Creating Fan...");
      if (currentActuator != nullptr) {
        currentActuator->deactivate();
        delete currentActuator;
      }
      currentActuator = ActuatorFactory::createActuator("fan", 6);
      if (currentActuator != nullptr) {
        Serial.println("Fan created and ready");
      }
      break;
      
    case 'a':
    case 'A':
      if (currentActuator != nullptr) {
        Serial.println("\n> Activating actuator...");
        currentActuator->activate();
        Serial.println("Activated");
      } else {
        Serial.println("\n> No actuator created yet!");
      }
      break;
      
    case 'd':
    case 'D':
      if (currentActuator != nullptr) {
        Serial.println("\n> Deactivating actuator...");
        currentActuator->deactivate();
        Serial.println("Deactivated");
      } else {
        Serial.println("\n> No actuator created yet!");
      }
      break;
      
    case '+':
      if (currentActuator != nullptr) {
        int currentValue = currentActuator->getValue();
        int newValue = currentValue + 20;
        currentActuator->setValue(newValue);
        Serial.print("\n> Increased to: ");
        Serial.println(newValue);
      } else {
        Serial.println("\n> No actuator created yet!");
      }
      break;
      
    case '-':
      if (currentActuator != nullptr) {
        int currentValue = currentActuator->getValue();
        int newValue = currentValue - 20;
        currentActuator->setValue(newValue);
        Serial.print("\n> Decreased to: ");
        Serial.println(newValue);
      } else {
        Serial.println("\n> No actuator created yet!");
      }
      break;
      
    case 's':
    case 'S':
      Serial.println("\n--- Actuator Status ---");
      if (currentActuator != nullptr) {
        Serial.print("Type: ");
        Serial.println(currentActuator->getType());
        Serial.print("Current Value: ");
        Serial.println(currentActuator->getValue());
      } else {
        Serial.println("No actuator created");
      }
      Serial.println("----------------------");
      break;
  }
}

/*
 * PEDAGOGICAL REFLECTIONS:
 * 
 * 1. FACTORY PATTERN BENEFITS:
 *    - Centralized creation: All actuator creation happens in one place
 *    - Type flexibility: Easy to create different actuators at runtime
 *    - Error handling: Factory can validate and return nullptr for invalid types
 *    - Configuration-driven: Can select actuator type from config/user input
 * 
 * 2. POLYMORPHISM IN ACTION:
 *    - Single Actuator* pointer works with Motor, Servo, or Fan
 *    - Same method calls (activate, setValue) produce different behaviors
 *    - Client code doesn't need to know the concrete type
 * 
 * 3. LOOSE COUPLING:
 *    - Main code doesn't depend on specific actuator classes
 *    - Can add new actuator types without changing this file
 *    - Only the factory needs to know about concrete classes
 * 
 * 4. OPEN-CLOSED PRINCIPLE:
 *    - Open for extension: Add new actuators by creating new classes
 *    - Closed for modification: Don't need to change existing client code
 *    - Factory is the only place that needs updates for new types
 * 
 * 5. REAL-WORLD APPLICATIONS:
 *    - IoT systems with swappable components
 *    - Robotics with modular actuators
 *    - Product lines with different hardware configurations
 *    - Testing with mock/simulated actuators
 * 
 * DISCUSSION QUESTIONS FOR STUDENTS:
 * - How would you add a new "LED" actuator type?
 * - What changes are needed in existing code when adding new types?
 * - How does the factory pattern reduce coupling?
 * - Why is returning nullptr better than throwing an exception here?
 * - How could you load actuator configuration from a file or EEPROM?
 * - What happens if you forget to delete an actuator? (memory leak)
 */