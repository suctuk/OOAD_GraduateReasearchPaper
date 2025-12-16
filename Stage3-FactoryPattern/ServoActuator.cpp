/*
 * ServoActuator.cpp
 * 
 * Implementation of the ServoActuator class.
 * Controls standard hobby servo motors (0-180 degrees).
 */

#include "ServoActuator.h"

ServoActuator::ServoActuator(int servoPin) {
  pin = servoPin;
  currentAngle = 90;  // Default to center position
  isActive = false;
}

void ServoActuator::activate() {
  if (!isActive) {
    servo.attach(pin);
    isActive = true;
    servo.write(currentAngle);  // Move to current angle
  }
}

void ServoActuator::deactivate() {
  if (isActive) {
    servo.detach();
    isActive = false;
  }
}

void ServoActuator::setValue(int value) {
  // For servos, value represents angle (0-180)
  setAngle(value);
}

int ServoActuator::getValue() {
  return currentAngle;
}

String ServoActuator::getType() {
  return "Servo";
}

void ServoActuator::setAngle(int angle) {
  // Constrain angle to valid servo range (0-180)
  currentAngle = constrain(angle, 0, 180);
  
  if (isActive) {
    servo.write(currentAngle);
  }
}

void ServoActuator::sweep(int startAngle, int endAngle, int delayMs) {
  if (!isActive) return;
  
  if (startAngle < endAngle) {
    // Sweep forward
    for (int angle = startAngle; angle <= endAngle; angle++) {
      setAngle(angle);
      delay(delayMs);
    }
  } else {
    // Sweep backward
    for (int angle = startAngle; angle >= endAngle; angle--) {
      setAngle(angle);
      delay(delayMs);
    }
  }
}
