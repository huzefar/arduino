#include "motor_control.h"

MotorControl::MotorControl(uint8_t enablePin, uint8_t in1Pin, uint8_t in2Pin)
    : _enablePin(enablePin), _in1Pin(in1Pin), _in2Pin(in2Pin) {}

void MotorControl::begin() {
  pinMode(_enablePin, OUTPUT);
  pinMode(_in1Pin,    OUTPUT);
  pinMode(_in2Pin,    OUTPUT);
  stop();
}

void MotorControl::forward(uint8_t speed) {
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);
  analogWrite(_enablePin, speed);
}

void MotorControl::backward(uint8_t speed) {
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);
  analogWrite(_enablePin, speed);
}

void MotorControl::stop() {
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
  analogWrite(_enablePin, 0);
}
