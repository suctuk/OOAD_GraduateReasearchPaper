#include "UltrasonicSensor.h"
#include "Arduino.h"

void UltrasonicSensor::begin() {
    // Initialize ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float UltrasonicSensor::readValue() {
    // Send ultrasonic pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read the echo time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate distance in centimeters
    // Speed of sound is 343 m/s or 0.0343 cm/microsecond
    // Distance = (duration * 0.0343) / 2 (divide by 2 for round trip)
    float distance = (duration * 0.0343) / 2.0;
    
    return distance;
}
