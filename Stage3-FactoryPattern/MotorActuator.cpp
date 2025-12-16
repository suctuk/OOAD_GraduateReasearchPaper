/*
 * MotorActuator.cpp
 * 
 * Implementation of the MotorActuator class.
 * Controls DC motors using PWM for speed control.
 */

#include "MotorActuator.h"

// Constructor for simple motor (speed control only)
MotorActuator::MotorActuator(int sPin) {
  speedPin = sPin;
  directionPin = -1;  // No direction pin
  currentSpeed = 0;
  isActive = false;
  pinMode(speedPin, OUTPUT);
  analogWrite(speedPin, 0);  // Start with motor off
}

// Constructor for motor with direction control
MotorActuator::MotorActuator(int sPin, int dPin) {
  speedPin = sPin;
  directionPin = dPin;
  currentSpeed = 0;
  isActive = false;
  pinMode(speedPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  analogWrite(speedPin, 0);
  digitalWrite(directionPin, LOW);
}

void MotorActuator::activate() {
  isActive = true;
  // Set to last known speed, or minimum speed if was 0
  if (currentSpeed == 0) {
    currentSpeed = 100;  // Default starting speed
  }
  analogWrite(speedPin, currentSpeed);
}

void MotorActuator::deactivate() {
  isActive = false;
  analogWrite(speedPin, 0);  // Stop motor
}

void MotorActuator::setValue(int value) {
  // Constrain value to valid PWM range (0-255)
  currentSpeed = constrain(value, 0, 255);
  
  if (isActive) {
    analogWrite(speedPin, currentSpeed);
  }
}

int MotorActuator::getValue() {
  return currentSpeed;
}

String MotorActuator::getType() {
  return "Motor";
}

void MotorActuator::setDirection(bool forward) {
  if (directionPin != -1) {
    digitalWrite(directionPin, forward ? HIGH : LOW);
  }
}
