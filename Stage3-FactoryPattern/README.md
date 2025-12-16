# Stage 3: Factory Pattern - Hardware Setup Guide

## File Structure
```
Stage3-FactoryPattern/
├── Actuator.h              - Abstract base class
├── Actuator.cpp            - Base class implementation
├── MotorActuator.h         - Motor header
├── MotorActuator.cpp       - Motor implementation
├── ServoActuator.h         - Servo header
├── ServoActuator.cpp       - Servo implementation
├── FanActuator.h           - Fan header
├── FanActuator.cpp         - Fan implementation
├── ActuatorFactory.h       - Factory class
└── Stage3.ino              - Main Arduino sketch
```

## Hardware Options for Arduino Uno

### Option 1: Servo Motor (EASIEST - Recommended for Testing)
**Components:**
- Arduino Uno
- Standard hobby servo (SG90 or similar)
- USB cable for power

**Connections:**
- Servo Signal (Orange/Yellow) → Arduino Pin 9
- Servo VCC (Red) → Arduino 5V
- Servo GND (Brown/Black) → Arduino GND

**Code Setup:**
In `Stage3.ino`, line 53, use:
```cpp
String actuatorType = "servo";
```

### Option 2: DC Motor
**Components:**
- Arduino Uno
- DC Motor (3-6V)
- Motor driver (L298N, L293D, or transistor circuit)
- External power supply (batteries)

**Connections:**
- Motor Driver Input → Arduino Pin 5 (PWM)
- Motor → Motor Driver Output
- Motor Driver Power → External battery
- Arduino GND → Motor Driver GND (common ground!)

**Code Setup:**
```cpp
String actuatorType = "motor";
```

### Option 3: DC Fan
**Components:**
- Arduino Uno
- Small DC fan (5V)
- NPN Transistor (2N2222 or similar)
- 1kΩ resistor
- Diode (1N4007) for protection

**Connections:**
- Arduino Pin 6 → 1kΩ Resistor → Transistor Base
- Fan Positive → Arduino 5V (or external power)
- Fan Negative → Transistor Collector
- Transistor Emitter → GND
- Diode across fan (cathode to positive)

**Code Setup:**
```cpp
String actuatorType = "fan";
```

## Uploading to Arduino Uno

### Using Arduino IDE:
1. Open `Stage3.ino` in Arduino IDE
2. Select **Tools → Board → Arduino Uno**
3. Select **Tools → Port → [Your Arduino Port]**
4. Click **Upload** (→ button)
5. Open **Tools → Serial Monitor** (set to 9600 baud)

### Expected Serial Output:
```
========================================
Stage 3: Factory Design Pattern
========================================

--- Demonstration 1: Basic Factory Usage ---
Creating a Motor actuator using factory...
...
```

## Troubleshooting

### Compilation Errors:

**Error: "Servo.h: No such file or directory"**
- Solution: The Servo library is built-in. Restart Arduino IDE.

**Error: "Multiple definition of..."**
- Solution: Make sure all .cpp files are in the same folder as the .ino file.

**Error: "Actuator does not name a type"**
- Solution: Check that all #include statements are present and files are saved.

### Runtime Issues:

**Servo jitters or doesn't move smoothly:**
- Use external power supply (not USB power)
- Ensure common ground between Arduino and power supply
- Check servo is rated for 5V

**Motor doesn't spin:**
- Verify motor driver connections
- Check external power supply voltage
- Ensure common ground
- Test with higher setValue() values (150-255)

**Nothing happens:**
- Open Serial Monitor (9600 baud)
- Check for error messages
- Verify actuatorType is spelled correctly
- Ensure actuator is connected to correct pin

## Testing Without Hardware

You can test the Factory Pattern logic without any hardware:

1. Upload the code to Arduino Uno
2. Open Serial Monitor (9600 baud)
3. Watch the demonstration output
4. The code logic will work even if no hardware is connected
5. Use interactive commands: 1, 2, 3, a, d, +, -, s

## Interactive Commands

Once uploaded, send these commands via Serial Monitor:

- `1` - Create Motor actuator
- `2` - Create Servo actuator
- `3` - Create Fan actuator
- `a` - Activate current actuator
- `d` - Deactivate current actuator
- `+` - Increase value by 20
- `-` - Decrease value by 20
- `s` - Show current status

## Design Pattern Verification

To verify the Factory Pattern is working:

1. **Test 1**: Change `actuatorType` from "servo" to "motor"
   - Upload code
   - Observe different behavior with same method calls

2. **Test 2**: Use interactive mode
   - Create servo (command: 2)
   - Create motor (command: 1)
   - Note how same interface works for both

3. **Test 3**: Add error handling
   - Change `actuatorType` to "invalid"
   - Observe nullptr handling

## Pin Summary for Arduino Uno

| Actuator Type | Pin(s)        | Type |
|---------------|---------------|------|
| Motor         | 5 (6 optional)| PWM  |
| Servo         | 9             | Digital |
| Fan           | 6             | PWM  |

## Memory Usage

Approximate memory usage on Arduino Uno:
- Sketch: ~6-8 KB of 32 KB Flash
- Global variables: ~400-600 bytes of 2 KB SRAM
- Plenty of room for expansion!

## Adding New Actuator Types

To add a new actuator (e.g., LED):

1. Create `LEDActuator.h` and `LEDActuator.cpp`
2. Inherit from `Actuator` base class
3. Implement all pure virtual methods
4. Add to `ActuatorFactory.h` in `createActuator()` method
5. No changes needed to `Stage3.ino`!

This demonstrates the Open-Closed Principle!
