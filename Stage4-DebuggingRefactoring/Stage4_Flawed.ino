/*
 * Stage4_Flawed.ino
 * Intentionally flawed sketch for debugging & refactoring practice.
 * Compiles and runs, but behavior is incorrect and design is messy.
 *
 * Known issues to find & fix (not exhaustive):
 * - Wrong pin assignments vs. stated hardware
 * - Inconsistent state updates (values not stored)
 * - Duplicated logic across sensors
 * - Leaky encapsulation (public data and direct pin writes)
 * - Factory returns partially configured objects
 * - Mixed responsibilities in the main loop
 */

#include <Arduino.h>

// --- Sensor hierarchy (simplified from Stage 2) ---
class Sensor {
  public:
    virtual void begin() = 0;
    virtual int readValue() = 0; // Return raw reading 0-1023
    virtual const char* getName() = 0;
    virtual ~Sensor() {}
};

class TemperatureSensor : public Sensor {
  public:
    int pin; // BUG: public pin leaks encapsulation
    TemperatureSensor(int p) : pin(p) {}
    void begin() override {
      pinMode(pin, INPUT);
    }
    int readValue() override {
      // BUG: should be analogRead(pin) but uses wrong pin A1 always
      return analogRead(A1);
    }
    const char* getName() override { return "Temp"; }
};

class LightSensor : public Sensor {
  public:
    int pin;
    LightSensor(int p) : pin(p) {}
    void begin() override {
      pinMode(pin, INPUT);
    }
    int readValue() override {
      return analogRead(pin);
    }
    const char* getName() override { return "Light"; }
};

// --- Actuator interface and a single concrete type (simplified from Stage 3) ---
class Actuator {
  public:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void setValue(int value) = 0; // 0-255 for PWM
    virtual int getValue() = 0;
    virtual const char* getType() = 0;
    virtual ~Actuator() {}
};

class MotorActuator : public Actuator {
  public:
    int speedPin;        // BUG: should be private
    int directionPin;    // Optional
    bool isActive;
    int lastWritten;     // BUG: never updated in setValue()
    MotorActuator(int sPin, int dPin = -1) {
      speedPin = sPin;
      directionPin = dPin;
      isActive = false;
      lastWritten = 0;
      pinMode(speedPin, OUTPUT);
      if (directionPin != -1) pinMode(directionPin, OUTPUT);
    }
    void activate() override {
      isActive = true;
      analogWrite(speedPin, 180); // BUG: hard-coded speed, ignores state
    }
    void deactivate() override {
      isActive = false;
      analogWrite(speedPin, 0);
    }
    void setValue(int value) override {
      // BUG: missing state storage (lastWritten)
      // BUG: no constrain on value
      analogWrite(speedPin, value);
    }
    int getValue() override {
      return lastWritten; // BUG: always 0 because not stored
    }
    const char* getType() override { return "Motor"; }
};

// --- Factory (intentionally sloppy) ---
class ActuatorFactory {
  public:
    static Actuator* createActuator(const String& type) {
      if (type == "motor") {
        // BUG: pin 3 may conflict with Serial on some boards; mismatches README
        return new MotorActuator(3);
      }
      // BUG: no handling for other types, returns nullptr silently
      return nullptr;
    }
};

// --- Global objects (note mismatched pins vs. README) ---
Sensor* sensors[2] = {
  new TemperatureSensor(A1), // BUG: should be A0 per README
  new LightSensor(A1)
};
Actuator* motor = nullptr;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  Serial.println("Stage 4 - Flawed Build (for debugging)\n");

  // Initialize sensors (but we never check success)
  for (int i = 0; i < 2; ++i) {
    sensors[i]->begin();
  }

  // Create motor via factory (returns partially configured object)
  motor = ActuatorFactory::createActuator("motor");
  if (motor) {
    motor->activate();
  } else {
    Serial.println("ERROR: Factory returned null actuator!\n");
  }
}

void loop() {
  // Duplicated sensor reading logic; mixes responsibilities
  int tempRaw = sensors[0]->readValue();
  int lightRaw = sensors[1]->readValue();

  // Naive mapping: average sensors to motor speed
  int avg = (tempRaw + lightRaw) / 2;
  int pwm = map(avg, 0, 1023, 0, 255);

  // BUG: no constraining; no state update in actuator
  if (motor) {
    motor->setValue(pwm);
  }

  // Minimal (and misleading) telemetry
  Serial.print("Temp:"); Serial.print(tempRaw);
  Serial.print("  Light:"); Serial.print(lightRaw);
  Serial.print("  PWM:"); Serial.print(pwm);
  Serial.print("  Stored:"); Serial.println(motor ? motor->getValue() : -1);

  delay(800);
}
