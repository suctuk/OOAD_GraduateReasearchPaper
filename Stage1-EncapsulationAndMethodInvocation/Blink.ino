/*
 * Blink.ino
 * 
 * Stage 1: Demonstrating Encapsulation and Method Invocation
 * 
 * This Arduino sketch demonstrates fundamental Object-Oriented Programming concepts:
 * - ENCAPSULATION: Data and methods are bundled together in the LEDObject class
 * - METHOD INVOCATION: Calling object methods to perform actions
 * - ABSTRACTION: Hardware complexity is hidden behind a simple interface
 * - CONSTRUCTOR: Objects are initialized with specific configuration
 * 
 * Hardware Setup:
 * - Built-in LED on pin 13 (standard on most Arduino boards)
 * - Optional: External LEDs on pins 12 and 11 for multi-object demonstration
 * 
 * Learning Objectives:
 * 1. Understand how objects encapsulate state and behavior
 * 2. See how method calls change both internal state and observable behavior
 * 3. Learn why private data members protect object integrity
 * 4. Experience the benefits of abstraction in hardware control
 */

#include "LEDObject.h"

// OBJECT INSTANTIATION: Creating LED objects
// Each object has its own state (on/off) and pin assignment
// The constructor is called here: LEDObject(pin)
LEDObject onboardLED(13);  // Built-in LED on most Arduino boards
LEDObject externalLED1(12); // Optional external LED
LEDObject externalLED2(11); // Optional external LED

void setup() {
  // Initialize serial communication for demonstrating state inspection
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (needed for some boards)
  }
  
  Serial.println("========================================");
  Serial.println("Stage 1: Encapsulation & Method Invocation");
  Serial.println("========================================\n");
  
  // CONSTRUCTOR DEMONSTRATION:
  // No pinMode() or digitalWrite() needed here!
  // The LEDObject constructor already initialized the pins.
  // This demonstrates encapsulation - setup details are hidden.
  
  Serial.println("LEDs initialized through constructors.");
  Serial.println("Starting demonstration...\n");
  delay(2000);
}

void loop() {
  // ========================================
  // DEMONSTRATION 1: Basic Method Invocation
  // ========================================
  Serial.println("--- Demo 1: Basic On/Off Control ---");
  
  // METHOD INVOCATION: Calling turnOn() method
  // This changes both internal state (isOn) and hardware state (LED lights up)
  onboardLED.turnOn();
  Serial.print("Onboard LED turned ON. State: ");
  Serial.println(onboardLED.getState() ? "ON" : "OFF");
  delay(1000);
  
  // METHOD INVOCATION: Calling turnOff() method
  onboardLED.turnOff();
  Serial.print("Onboard LED turned OFF. State: ");
  Serial.println(onboardLED.getState() ? "ON" : "OFF");
  delay(1000);
  
  // ========================================
  // DEMONSTRATION 2: Toggle Method
  // ========================================
  Serial.println("\n--- Demo 2: Toggle Functionality ---");
  Serial.println("Toggling LED 5 times...");
  
  for (int i = 0; i < 5; i++) {
    onboardLED.toggle();  // Switch state
    Serial.print("Toggle ");
    Serial.print(i + 1);
    Serial.print(" - State: ");
    Serial.println(onboardLED.getState() ? "ON" : "OFF");
    delay(300);
  }
  
  // ========================================
  // DEMONSTRATION 3: Blink Method
  // ========================================
  Serial.println("\n--- Demo 3: Blink Method ---");
  Serial.println("Blinking with different durations...");
  
  onboardLED.blink(200);  // Short blink
  delay(500);
  onboardLED.blink(500);  // Medium blink
  delay(500);
  onboardLED.blink(1000); // Long blink
  delay(500);
  
  // ========================================
  // DEMONSTRATION 4: Multiple Objects
  // ========================================
  Serial.println("\n--- Demo 4: Multiple Independent Objects ---");
  Serial.println("Each object maintains its own state!");
  
  // Turn on different LEDs independently
  onboardLED.turnOn();
  Serial.println("Onboard LED: ON");
  delay(500);
  
  externalLED1.turnOn();
  Serial.println("External LED 1: ON");
  delay(500);
  
  externalLED2.turnOn();
  Serial.println("External LED 2: ON");
  delay(500);
  
  // Turn them off in different order
  externalLED1.turnOff();
  Serial.println("External LED 1: OFF");
  delay(500);
  
  onboardLED.turnOff();
  Serial.println("Onboard LED: OFF");
  delay(500);
  
  externalLED2.turnOff();
  Serial.println("External LED 2: OFF");
  delay(500);
  
  // ========================================
  // DEMONSTRATION 5: State Inspection
  // ========================================
  Serial.println("\n--- Demo 5: Accessing Object State ---");
  
  onboardLED.turnOn();
  
  // ACCESSOR METHOD: Using getState() to inspect private data
  // We can read the state, but cannot directly modify isOn
  if (onboardLED.getState()) {
    Serial.println("LED is currently ON");
    Serial.print("Connected to pin: ");
    Serial.println(onboardLED.getPin());
  }
  
  delay(1000);
  onboardLED.turnOff();
  
  // ========================================
  // DEMONSTRATION 6: Synchronized Pattern
  // ========================================
  Serial.println("\n--- Demo 6: Coordinated LED Pattern ---");
  Serial.println("Creating a wave pattern...");
  
  for (int i = 0; i < 3; i++) {
    onboardLED.turnOn();
    delay(200);
    externalLED1.turnOn();
    delay(200);
    externalLED2.turnOn();
    delay(200);
    
    onboardLED.turnOff();
    delay(200);
    externalLED1.turnOff();
    delay(200);
    externalLED2.turnOff();
    delay(200);
  }
  
  Serial.println("\n========================================");
  Serial.println("Demonstration cycle complete!");
  Serial.println("Restarting in 3 seconds...\n");
  delay(3000);
}

/*
 * PEDAGOGICAL REFLECTIONS:
 * 
 * 1. ENCAPSULATION IN ACTION:
 *    - The 'isOn' variable is private - you cannot write: led.isOn = true
 *    - You must use led.turnOn() which ensures hardware and state stay synchronized
 *    - This prevents bugs from direct state manipulation
 * 
 * 2. METHOD INVOCATION:
 *    - Each method call (turnOn, turnOff, toggle) triggers specific behavior
 *    - Methods combine state changes with hardware control
 *    - Higher-level methods (blink, toggle) build on basic methods
 * 
 * 3. ABSTRACTION:
 *    - Users don't need to know about digitalWrite() or pinMode()
 *    - The interface is intuitive: turnOn(), turnOff(), toggle()
 *    - Implementation details are hidden in LEDObject.cpp
 * 
 * 4. OBJECT INDEPENDENCE:
 *    - Each LED object maintains its own state
 *    - Multiple objects can coexist without interference
 *    - Demonstrates the power of OOP for managing complexity
 * 
 * 5. OBSERVABLE BEHAVIOR:
 *    - Physical LED provides immediate feedback
 *    - Reduces cognitive load - students see state changes happen
 *    - Links abstract code concepts to tangible results
 * 
 * DISCUSSION QUESTIONS FOR STUDENTS:
 * - Why is 'isOn' private instead of public?
 * - What could go wrong if we could directly set isOn without using methods?
 * - How does encapsulation make the code more maintainable?
 * - What would we need to change to add brightness control (PWM)?
 * - How does the constructor simplify the setup() function?
 */