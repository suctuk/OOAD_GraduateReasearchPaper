#include "LEDObject.h"
#include <Arduino.h>

LEDObject::LEDObject(int pin) {
  ledPin = pin;
  isOn = false;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void LEDObject::turnOn() {
  digitalWrite(ledPin, HIGH);
  isOn = true;
}

void LEDObject::turnOff() {
  digitalWrite(ledPin, LOW);
  isOn = false;
}

bool LEDObject::getState() {
  return isOn;
}