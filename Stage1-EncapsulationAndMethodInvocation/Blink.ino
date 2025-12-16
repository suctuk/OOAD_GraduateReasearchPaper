#include "LEDObject.h"

LEDObject led(13); 
// using pin 13 for onboard LED

void setup() {
  // nothing else needed, 
  // LEDObject constructor sets up the pin
}

void loop() {
  led.turnOn();
  delay(500);
  led.turnOff();
  delay(500);
}