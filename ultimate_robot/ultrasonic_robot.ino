/*
 * Ultrasonic Sensor Robot
 *
 * An obstacle-avoiding robot that uses an HC-SR04 ultrasonic sensor
 * to detect obstacles and navigate around them.
 *
 * Hardware:
 *   - Arduino Uno/Nano
 *   - HC-SR04 Ultrasonic Sensor
 *   - L298N Motor Driver
 *   - 2x DC Motors (left & right)
 *   - Servo motor (optional, for sensor sweeping)
 */

#include "motor_control.h"
#include "ultrasonic_sensor.h"
#include <Servo.h>

// --- Pin Definitions ---

// Ultrasonic sensor
static const uint8_t TRIG_PIN = 9;
static const uint8_t ECHO_PIN = 10;

// Motor driver (L298N)
static const uint8_t LEFT_MOTOR_EN  = 5;   // ENA (PWM)
static const uint8_t LEFT_MOTOR_IN1 = 2;
static const uint8_t LEFT_MOTOR_IN2 = 3;

static const uint8_t RIGHT_MOTOR_EN  = 6;  // ENB (PWM)
static const uint8_t RIGHT_MOTOR_IN1 = 4;
static const uint8_t RIGHT_MOTOR_IN2 = 7;

// Servo for sensor sweep (optional)
static const uint8_t SERVO_PIN = 11;

// --- Thresholds ---
static const unsigned int OBSTACLE_DISTANCE_CM = 30;  // Stop if closer than this
static const unsigned int TURN_DISTANCE_CM     = 50;  // Slow down if closer than this
static const uint8_t      DRIVE_SPEED          = 180; // 0-255
static const uint8_t      TURN_SPEED           = 150;

// --- Global Objects ---
UltrasonicSensor sensor(TRIG_PIN, ECHO_PIN);
MotorControl leftMotor(LEFT_MOTOR_EN, LEFT_MOTOR_IN1, LEFT_MOTOR_IN2);
MotorControl rightMotor(RIGHT_MOTOR_EN, RIGHT_MOTOR_IN1, RIGHT_MOTOR_IN2);
Servo scanServo;

// --- Prototypes ---
void driveForward(uint8_t speed);
void driveBackward(uint8_t speed);
void turnLeft(uint8_t speed);
void turnRight(uint8_t speed);
void stopMotors();
unsigned int scanDirection(int angle);
void avoidObstacle();

// ===================== setup =====================
void setup() {
  Serial.begin(9600);
  sensor.begin();
  leftMotor.begin();
  rightMotor.begin();

  scanServo.attach(SERVO_PIN);
  scanServo.write(90);  // Centre the sensor
  delay(500);

  Serial.println(F("Ultrasonic Robot ready."));
}

// ===================== loop ======================
void loop() {
  unsigned int distance = sensor.readDistanceCm();

  Serial.print(F("Distance: "));
  Serial.print(distance);
  Serial.println(F(" cm"));

  if (distance > 0 && distance < OBSTACLE_DISTANCE_CM) {
    // Obstacle very close — stop and decide
    stopMotors();
    delay(100);
    avoidObstacle();
  } else if (distance > 0 && distance < TURN_DISTANCE_CM) {
    // Getting close — slow down
    driveForward(TURN_SPEED);
  } else {
    // Clear ahead
    driveForward(DRIVE_SPEED);
  }

  delay(50);
}

// ============= Motion helpers ====================

void driveForward(uint8_t speed) {
  leftMotor.forward(speed);
  rightMotor.forward(speed);
}

void driveBackward(uint8_t speed) {
  leftMotor.backward(speed);
  rightMotor.backward(speed);
}

void turnLeft(uint8_t speed) {
  leftMotor.backward(speed);
  rightMotor.forward(speed);
}

void turnRight(uint8_t speed) {
  leftMotor.forward(speed);
  rightMotor.backward(speed);
}

void stopMotors() {
  leftMotor.stop();
  rightMotor.stop();
}

// ============= Obstacle avoidance ================

unsigned int scanDirection(int angle) {
  scanServo.write(angle);
  delay(350);  // Wait for servo to reach position
  return sensor.readDistanceCm();
}

void avoidObstacle() {
  // Back up a little
  driveBackward(TURN_SPEED);
  delay(300);
  stopMotors();
  delay(200);

  // Look left and right
  unsigned int distLeft  = scanDirection(160);
  unsigned int distRight = scanDirection(20);

  // Return sensor to centre
  scanServo.write(90);
  delay(200);

  Serial.print(F("Left: "));
  Serial.print(distLeft);
  Serial.print(F(" cm  Right: "));
  Serial.print(distRight);
  Serial.println(F(" cm"));

  // Turn towards the side with more open space
  if (distLeft >= distRight) {
    turnLeft(TURN_SPEED);
  } else {
    turnRight(TURN_SPEED);
  }
  delay(400);  // Adjust for ~90° turn at TURN_SPEED
  stopMotors();
  delay(100);
}
