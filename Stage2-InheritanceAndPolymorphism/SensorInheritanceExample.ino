/*
 * SensorInheritanceExample.ino
 * 
 * Demonstrates inheritance and polymorphism using an abstract Sensor base class.
 * This sketch creates multiple sensor objects and uses base class pointers to
 * interact with them polymorphically, showcasing runtime polymorphism.
 * 
 * Hardware Connections:
 * - Temperature Sensor: Connected to analog pin A0
 * - Light Sensor: Connected to analog pin A1
 * - Ultrasonic Sensor: Trigger pin on D7, Echo pin on D8
 */

#include "Sensor.h"
#include "TemperatureSensor.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"

// Array of base class pointers demonstrating polymorphism
const int NUM_SENSORS = 3;
Sensor* sensors[NUM_SENSORS];

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect (needed for some boards)
    }
    
    Serial.println("=================================");
    Serial.println("Sensor Inheritance Example");
    Serial.println("Demonstrating Polymorphism");
    Serial.println("=================================\n");
    
    // Create sensor objects using base class pointers
    // This demonstrates runtime polymorphism
    sensors[0] = new TemperatureSensor(A0);
    sensors[1] = new LightSensor(A1);
    sensors[2] = new UltrasonicSensor(7, 8);  // Trigger pin 7, Echo pin 8
    
    // Initialize all sensors polymorphically
    // Each sensor's specific begin() method is called
    Serial.println("Initializing sensors...");
    for (int i = 0; i < NUM_SENSORS; ++i) {
        sensors[i]->begin();
    }
    Serial.println("All sensors initialized!\n");
    delay(1000);
}

void loop() {
    Serial.println("--- Sensor Readings ---");
    
    // Polymorphic call to readValue()
    // The actual method executed depends on the runtime type of each object
    Serial.print("Temperature Sensor: ");
    Serial.print(sensors[0]->readValue());
    Serial.println(" V");
    
    Serial.print("Light Sensor: ");
    Serial.print(sensors[1]->readValue());
    Serial.println(" %");
    
    Serial.print("Ultrasonic Sensor: ");
    Serial.print(sensors[2]->readValue());
    Serial.println(" cm");
    
    Serial.println();
    delay(2000);  // Wait 2 seconds before next reading
}

/*
 * Key OOP Concepts Demonstrated:
 * 
 * 1. Abstraction: Sensor is an abstract base class with pure virtual functions
 * 2. Inheritance: TemperatureSensor, LightSensor, and UltrasonicSensor inherit from Sensor
 * 3. Polymorphism: Base class pointers are used to call overridden methods
 * 4. Encapsulation: Each sensor class encapsulates its specific hardware logic
 * 5. Virtual Functions: begin() and readValue() are overridden in derived classes
 * 
 * Benefits:
 * - New sensor types can be added without modifying existing code
 * - Main logic doesn't need to know specific sensor types
 * - Code is more maintainable and scalable
 */