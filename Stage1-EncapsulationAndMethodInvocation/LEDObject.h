//LEDObject.h
#ifndef LEDOBJECT_H
#define LEDOBJECT_H

class LEDObject {
  private:
    int ledPin;
    bool isOn;

  public:
    LEDObject(int pin);
    void turnOn();
    void turnOff();
    bool getState();
};

#endif