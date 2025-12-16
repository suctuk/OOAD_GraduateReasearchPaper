/*
 * FanActuator.cpp
 * 
 * Implementation of the FanActuator class.
 * Controls DC cooling fans using PWM for speed control.
 */

#include "FanActuator.h"

FanActuator::FanActuator(int fanPin) {
  pin = fanPin;
  currentSpeed = 0;
  isActive = false;
  pinMode(pin, OUTPUT);
  analogWrite(pin, 0);  // Start with fan off
}

void FanActuator::activate() {
  isActive = true;
  // Set to last known speed, or medium speed if was 0
  if (currentSpeed == 0) {
    currentSpeed = 150;  // Default medium speed
  }
  analogWrite(pin, currentSpeed);
}

void FanActuator::deactivate() {
  isActive = false;
  analogWrite(pin, 0);  // Stop fan
}

void FanActuator::setValue(int value) {
  setSpeed(value);
}

int FanActuator::getValue() {
  return currentSpeed;
}

String FanActuator::getType() {
  return "Fan";
}

void FanActuator::setSpeed(int speed) {
  // Constrain speed to valid PWM range (0-255)
  currentSpeed = constrain(speed, 0, 255);
  
  if (isActive) {
    analogWrite(pin, currentSpeed);
  }
}
