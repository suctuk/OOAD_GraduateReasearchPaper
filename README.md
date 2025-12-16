# OOAD Graduate Research Paper — Arduino OOP Teaching Trajectory

This repository contains a 4-stage, hands-on trajectory for teaching Object-Oriented Analysis & Design (OOAD) using Arduino-based physical computing. Each stage introduces core OOP concepts with progressively richer abstractions and patterns, grounded in tangible sensor/actuator behaviors.

## Repository Structure

- `Stage1-EncapsulationAndMethodInvocation/` — Encapsulation with `LEDObject` and method calls
- `Stage2-InheritanceAndPolymorphism/` — Abstract `Sensor` base class, derived sensors, polymorphic usage
- `Stage3-FactoryPattern/` — Polymorphic `Actuator` hierarchy and `ActuatorFactory`
- `Stage4-DebuggingRefactoring/` — Intentionally flawed build + refactored solution for debugging/design practice

## Prerequisites

- Hardware: Arduino Uno (or compatible), USB cable
- Sensors/Actuators (pick per stage):
  - Stage 1: Onboard LED (D13) or external LEDs (D11, D12)
  - Stage 2: Analog sensors (e.g., temperature on A0, light on A1), optional ultrasonic (Trig D7, Echo D8)
  - Stage 3: Servo (D9), DC motor/fan via PWM (D5/D6) and driver/transistor
  - Stage 4: Temperature sensor (A0), light sensor (A1), motor PWM (D5), optional direction (D6)
- Software options:
  - Arduino IDE (recommended for uploading)
  - Alternatively: VS Code with Arduino extension

## Setup: Arduino IDE (recommended)

1. Install Arduino IDE from arduino.cc.
2. Connect your Arduino Uno via USB.
3. In Arduino IDE:
   - Select board: Tools → Board → Arduino Uno
   - Select port: Tools → Port → your device
4. Open the sketch file (`.ino`) for the stage you want.
5. Click Upload.
6. Open Serial Monitor (Tools → Serial Monitor) and set baud to `9600` when applicable.

## Setup: VS Code (alternative)

1. Install extensions:
   - "Arduino" by Microsoft
2. Configure Arduino path in VS Code settings (if prompted).
3. Open this repository folder in VS Code.
4. For each stage, open the corresponding `.ino` file.
5. Use the VS Code Arduino status bar to select board (Arduino Uno) and port.
6. Click "Upload" or "Verify"; open the Serial Monitor at `9600` baud.

## How to Run Each Stage

### Stage 1 — Encapsulation & Method Invocation
- Files: `LEDObject.h`, `LEDObject.cpp`, `Blink.ino`
- Hardware: Built-in LED on D13 (optional external LEDs on D12/D11)
- Steps:
  - Open `Blink.ino` and upload.
  - Observe LED behavior; open Serial Monitor for prompts when present.
- Concepts: private state (`isOn`), public methods (`turnOn`, `turnOff`, `toggle`, `blink`), constructor-controlled setup.

### Stage 2 — Inheritance & Polymorphism
- Files: `Sensor.h`, `Sensor.cpp`, `TemperatureSensor.*`, `LightSensor.*`, `UltrasonicSensor.*`, `SensorInheritanceExample.ino`
- Hardware:
  - Temperature sensor → A0
  - Light sensor → A1
  - Ultrasonic → Trig D7, Echo D8
- Steps:
  - Open `SensorInheritanceExample.ino` and upload.
  - Serial Monitor @ `9600` shows readings with units.
- Concepts: abstract base class (`Sensor`), overridden `begin()/readValue()`, array of `Sensor*` demonstrating runtime polymorphism.

### Stage 3 — Factory Pattern with Actuators
- Files: `Actuator.*`, `MotorActuator.*`, `ServoActuator.*`, `FanActuator.*`, `ActuatorFactory.h`, `Stage3.ino`, `QuickTest.ino`, `README.md`
- Hardware options:
  - Servo → D9
  - Motor via driver → PWM D5 (optional dir D6)
  - Fan via transistor → PWM D6
- Quick verification (no hardware required): open `QuickTest.ino`, upload, watch Serial tests.
- Full demo: open `Stage3.ino`, upload, use Serial Monitor commands:
  - `1` motor, `2` servo, `3` fan
  - `a` activate, `d` deactivate, `+` increase, `-` decrease, `s` status
- Concepts: factory method returns `Actuator*`, polymorphic calls across `Motor/Servo/Fan`, loose coupling, open–closed principle.

### Stage 4 — Debugging & Refactoring (optional)
- Files: `Stage4_Flawed.ino` (students), `Stage4_Refactored.ino` (reference), `README.md`
- Hardware: A0 temp, A1 light, D5 PWM motor, optional D6 dir.
- Steps:
  - Start with `Stage4_Flawed.ino`; upload and observe mismatches.
  - Use Serial, pin maps, and incremental fixes to restore behavior.
  - Compare with `Stage4_Refactored.ino` to discuss design improvements.
- Targets: fix pin mismatches, store & constrain state, remove duplication, tighten encapsulation, ensure factory responsibility.

## Common Troubleshooting

- Serial output is garbled or empty: ensure Serial Monitor baud is `9600` and the correct port is selected.
- Servo jitters or resets:
  - Use external power for the servo (shared ground with Arduino).
  - Avoid powering motors/servos directly from the 5V pin when possible.
- Motor/fan doesn’t spin:
  - Confirm driver/transistor wiring; use a known-good PWM pin (D5/D6).
  - Check `setValue()` ranges (0–255) and try higher values.
- VS Code IntelliSense errors (e.g., `Arduino.h` not found): upload via Arduino IDE; these are editor hints, not compile blockers.

## Safety & Power Notes

- Always share ground between Arduino and any external power supplies.
- Use drivers/transistors + flyback diodes for inductive loads (motors/fans).
- Avoid exceeding current limits of the Arduino’s 5V pin.

## Suggested Learning Path

1. Stage 1: Encapsulation on LEDs
2. Stage 2: Abstract classes + polymorphism with sensors
3. Stage 3: Factory pattern + actuators with interactive control
4. Stage 4: Debugging & refactoring (software/hardware mix)

## License & Attribution

- Educational use intended. Hardware wiring varies by component; verify datasheets.
- Code authored as part of OOAD teaching materials; adapt freely for classroom use.
