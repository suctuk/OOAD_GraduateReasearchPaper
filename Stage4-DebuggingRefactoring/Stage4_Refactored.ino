/*
 * Stage4_Refactored.ino
 * Clean, working version that fixes logic/design issues from Stage4_Flawed.ino.
 * Use this after students attempt the flawed version to discuss improvements.
 */

#include <Arduino.h>

// --- Sensor hierarchy (fixed) ---
class Sensor {
  public:
    virtual void begin() = 0;
    virtual int readValue() = 0; // 0-1023
    virtual const char* getName() = 0;
    virtual ~Sensor() {}
};

class AnalogSensor : public Sensor {
  protected:
    int pin;
    const char* name;
  public:
    AnalogSensor(int p, const char* n) : pin(p), name(n) {}
    void begin() override { pinMode(pin, INPUT); }
    int readValue() override { return analogRead(pin); }
    const char* getName() override { return name; }
};

class TemperatureSensor : public AnalogSensor {
  public:
    TemperatureSensor(int p) : AnalogSensor(p, "Temp") {}
};

class LightSensor : public AnalogSensor {
  public:
    LightSensor(int p) : AnalogSensor(p, "Light") {}
};

// --- Actuator interface and motor implementation (fixed) ---
class Actuator {
  public:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void setValue(int value) = 0;
    virtual int getValue() = 0;
    virtual const char* getType() = 0;
    virtual ~Actuator() {}
};

class MotorActuator : public Actuator {
  private:
    int speedPin;
    int directionPin;
    bool isActive;
    int currentPwm;
  public:
    MotorActuator(int sPin, int dPin = -1)
      : speedPin(sPin), directionPin(dPin), isActive(false), currentPwm(0) {
      pinMode(speedPin, OUTPUT);
      if (directionPin != -1) pinMode(directionPin, OUTPUT);
      analogWrite(speedPin, 0);
    }
    void activate() override {
      isActive = true;
      analogWrite(speedPin, currentPwm);
    }
    void deactivate() override {
      isActive = false;
      analogWrite(speedPin, 0);
    }
    void setValue(int value) override {
      currentPwm = constrain(value, 0, 255);
      if (isActive) {
        analogWrite(speedPin, currentPwm);
      }
    }
    int getValue() override { return currentPwm; }
    const char* getType() override { return "Motor"; }
};

// --- Factory (fixed, explicit, single responsibility) ---
class ActuatorFactory {
  public:
    static Actuator* createActuator(const String& type, int pin, int dirPin = -1) {
      String t = type; t.toLowerCase();
      if (t == "motor") return new MotorActuator(pin, dirPin);
      return nullptr;
    }
};

// --- Helper: map and clamp combined ---
int mapToPwm(int raw) {
  raw = constrain(raw, 0, 1023);
  return map(raw, 0, 1023, 0, 255);
}

// --- Application wiring (aligned with README) ---
const int TEMP_PIN = A0;
const int LIGHT_PIN = A1;
const int MOTOR_PWM_PIN = 5;   // PWM
const int MOTOR_DIR_PIN = 6;   // Optional; safe to leave unconnected if unused

Sensor* sensors[2] = {
  new TemperatureSensor(TEMP_PIN),
  new LightSensor(LIGHT_PIN)
};
Actuator* motor = nullptr;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  Serial.println("Stage 4 - Refactored Build\n");

  for (int i = 0; i < 2; ++i) sensors[i]->begin();

  motor = ActuatorFactory::createActuator("motor", MOTOR_PWM_PIN, MOTOR_DIR_PIN);
  if (motor) {
    motor->activate();
  } else {
    Serial.println("Factory failed: motor not created");
  }
}

void loop() {
  // Centralized sensor read
  int tempRaw = sensors[0]->readValue();
  int lightRaw = sensors[1]->readValue();

  // Cohesive transformation: compute PWM
  int avg = (tempRaw + lightRaw) / 2;
  int pwm = mapToPwm(avg);

  if (motor) {
    motor->setValue(pwm);
  }

  // Clear telemetry for debugging
  Serial.print("Temp:"); Serial.print(tempRaw);
  Serial.print("  Light:"); Serial.print(lightRaw);
  Serial.print("  PWM:"); Serial.print(pwm);
  Serial.print("  Stored:"); Serial.println(motor ? motor->getValue() : -1);

  delay(800);
}
