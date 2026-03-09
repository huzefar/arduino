#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

/**
 * Driver for the HC-SR04 ultrasonic distance sensor.
 */
class UltrasonicSensor {
public:
  UltrasonicSensor(uint8_t trigPin, uint8_t echoPin);

  void begin();

  /** Returns distance in centimetres (0 = out-of-range / no echo). */
  unsigned int readDistanceCm();

private:
  uint8_t _trigPin;
  uint8_t _echoPin;

  static const unsigned long TIMEOUT_US = 30000;  // ~5 m max range
};

#endif
