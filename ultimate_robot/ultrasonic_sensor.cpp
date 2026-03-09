#include "ultrasonic_sensor.h"

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin)
    : _trigPin(trigPin), _echoPin(echoPin) {}

void UltrasonicSensor::begin() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
  digitalWrite(_trigPin, LOW);
}

unsigned int UltrasonicSensor::readDistanceCm() {
  // Send a 10 µs trigger pulse
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Measure the echo pulse duration
  unsigned long duration = pulseIn(_echoPin, HIGH, TIMEOUT_US);

  if (duration == 0) {
    return 0;  // No echo received (out of range)
  }

  // Speed of sound ≈ 343 m/s → 0.0343 cm/µs
  // Distance = duration * 0.0343 / 2  (round-trip)
  unsigned int distanceCm = (unsigned int)(duration * 0.0343 / 2.0);
  return distanceCm;
}
