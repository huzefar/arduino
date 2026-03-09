#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

/**
 * Simple DC-motor driver via an H-bridge (L298N / L293D).
 * Each motor needs one PWM-capable enable pin and two direction pins.
 */
class MotorControl {
public:
  MotorControl(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin);

  void begin();
  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void stop();

private:
  uint8_t _enablePin;
  uint8_t _in1Pin;
  uint8_t _in2Pin;
};

#endif
