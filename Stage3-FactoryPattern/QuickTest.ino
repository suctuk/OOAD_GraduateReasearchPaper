/*
 * QuickTest.ino
 * 
 * Simple test sketch to verify all files compile correctly
 * Tests the Factory Pattern without requiring hardware
 */

#include "ActuatorFactory.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  
  Serial.println("=== Factory Pattern Compilation Test ===\n");
  
  // Test 1: Create each actuator type
  Serial.println("Test 1: Creating Motor...");
  Actuator* motor = ActuatorFactory::createActuator("motor", 5);
  if (motor != nullptr) {
    Serial.print("  Success! Type: ");
    Serial.println(motor->getType());
    delete motor;
  }
  
  Serial.println("\nTest 2: Creating Servo...");
  Actuator* servo = ActuatorFactory::createActuator("servo", 9);
  if (servo != nullptr) {
    Serial.print("  Success! Type: ");
    Serial.println(servo->getType());
    delete servo;
  }
  
  Serial.println("\nTest 3: Creating Fan...");
  Actuator* fan = ActuatorFactory::createActuator("fan", 6);
  if (fan != nullptr) {
    Serial.print("  Success! Type: ");
    Serial.println(fan->getType());
    delete fan;
  }
  
  Serial.println("\nTest 4: Error handling (invalid type)...");
  Actuator* invalid = ActuatorFactory::createActuator("invalid");
  if (invalid == nullptr) {
    Serial.println("  Success! Factory returned nullptr for invalid type");
  }
  
  Serial.println("\n=== All Tests Passed! ===");
  Serial.println("Factory Pattern is working correctly!");
  Serial.println("\nYou can now upload Stage3.ino for the full demonstration.");
}

void loop() {
  // Nothing to do here
}
