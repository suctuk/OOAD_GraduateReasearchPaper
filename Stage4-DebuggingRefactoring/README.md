# Stage 4: Debugging & Refactoring

This optional stage gives students a messy, realistic codebase to fix and improve. The goal is to diagnose bugs that mix software and hardware issues, restore correct behavior, and then refactor without changing external behavior.

## What’s included
- `Stage4_Flawed.ino` — intentionally flawed sketch (compiles, runs poorly)
- `Stage4_Refactored.ino` — cleaned, working reference solution

## Learning objectives
- Practice systematic debugging (hypothesis → test → observe → iterate)
- Differentiate hardware vs. software faults (pins, wiring, logic, state)
- Apply refactoring moves to improve cohesion, encapsulation, and clarity
- Preserve externally observable behavior while improving the design

## Suggested debugging workflow
1) **Read the symptoms**: Run `Stage4_Flawed.ino`, watch Serial output and hardware.
2) **Inspect wiring**: Verify pin map matches the code; fix obvious pin mismatches.
3) **Trace execution**: Add `Serial.print` breadcrumbs to locate logic errors.
4) **Check state**: Ensure internal state mirrors hardware (e.g., speed variables update when writing PWM).
5) **Isolate**: Disable one sensor/actuator at a time to separate issues.
6) **Fix, then refactor**: Once it works, remove duplication, tighten encapsulation, and move responsibilities to the right classes.

## Refactoring targets (shortlist)
- Remove duplicated sensor-reading loops; centralize in a helper.
- Fix leaky encapsulation (no public pins/state; use getters/setters).
- Ensure factories only create/return fully initialized objects.
- Align pin configuration with hardware; avoid magic numbers.
- Make state updates consistent (`setValue` should store and apply).
- Prefer single-responsibility classes; keep wiring/config separate from behavior.

## Hardware setup (kept simple)
- Temperature sensor on **A0**
- Light sensor on **A1**
- Motor (or fan) PWM on **D5** (via driver or transistor); direction pin optional on **D6**
- Optional servo on **D9** (used only in the refactored demo)

## How to use in class
- Give students only `Stage4_Flawed.ino` and the circuit.
- Ask them to:
  1) Identify and fix the bugs until the motor response matches sensor input.
  2) Refactor to remove duplication, fix encapsulation leaks, and clean the factory.
- Provide `Stage4_Refactored.ino` afterward for comparison and discussion.

## Reflection prompts
- Which bugs were hardware vs. software? How did you tell?
- What refactoring improved readability the most? Why?
- How did you ensure behavior stayed the same after refactoring?
- Where did the single-responsibility principle get violated? How did you fix it?
