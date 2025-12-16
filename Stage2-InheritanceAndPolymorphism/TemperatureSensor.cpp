#include "TemperatureSensor.h"

void TemperatureSensor::begin() {
    // Sensor specific initialization
    pinMode(pin, INPUT);
}

float TemperatureSensor::readValue() {
    // Example: 
    // analog temperature sensor reading
    int rawValue = analogRead(pin);
    return (float)rawValue * (5.0 / 1023.0); 
    // convert to volts, for example
}