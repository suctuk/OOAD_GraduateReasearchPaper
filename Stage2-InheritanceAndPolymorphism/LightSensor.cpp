#include "LightSensor.h"
#include "Arduino.h"

void LightSensor::begin() {
    // Initialize the light sensor pin
    pinMode(pin, INPUT);
}

float LightSensor::readValue() {
    // Read analog value from photoresistor/light sensor
    // Returns a value representing light intensity (0-1023 range)
    // Can be scaled to lux or percentage as needed
    int rawValue = analogRead(pin);
    // Convert to percentage (0-100%)
    return (rawValue / 1023.0) * 100.0;
}
