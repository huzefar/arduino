# Ultrasonic Sensor Robot

An obstacle-avoiding robot powered by an Arduino, an HC-SR04 ultrasonic sensor, and an L298N motor driver.

## How It Works

1. The ultrasonic sensor continuously measures the distance ahead.
2. If the path is clear (> 50 cm), the robot drives forward at full speed.
3. If an object is detected within 50 cm, the robot slows down.
4. If an obstacle is closer than 30 cm, the robot stops, backs up, sweeps the sensor left and right with a servo, and turns towards the side with more open space.

## Hardware Required

| Component             | Qty |
|-----------------------|-----|
| Arduino Uno / Nano    | 1   |
| HC-SR04 Ultrasonic    | 1   |
| L298N Motor Driver    | 1   |
| DC Geared Motors      | 2   |
| Servo Motor (SG90)    | 1   |
| Robot Chassis + Wheels| 1   |
| Battery Pack (7-12 V) | 1   |
| Jumper Wires          | —   |

## Wiring

### HC-SR04 → Arduino

| HC-SR04 Pin | Arduino Pin |
|-------------|-------------|
| VCC         | 5 V         |
| GND         | GND         |
| TRIG        | D9          |
| ECHO        | D10         |

### L298N → Arduino (Left Motor)

| L298N Pin | Arduino Pin |
|-----------|-------------|
| ENA       | D5 (PWM)    |
| IN1       | D2          |
| IN2       | D3          |

### L298N → Arduino (Right Motor)

| L298N Pin | Arduino Pin |
|-----------|-------------|
| ENB       | D6 (PWM)    |
| IN3       | D4          |
| IN4       | D7          |

### Servo → Arduino

| Servo Wire | Arduino Pin |
|------------|-------------|
| Signal     | D11         |
| VCC        | 5 V         |
| GND        | GND         |

### Power

- Connect the battery pack (7–12 V) to the L298N's **12 V** and **GND** terminals.
- Connect the L298N's **5 V output** to the Arduino's **5 V** pin (or power the Arduino separately via USB/barrel jack).

## Building & Uploading

1. Open `ultrasonic_robot.ino` in the **Arduino IDE**.
2. Select your board (**Tools → Board → Arduino Uno**).
3. Select the correct serial port (**Tools → Port**).
4. Click **Upload**.

## Tuning

You can adjust these constants in `ultrasonic_robot.ino` to suit your chassis and motors:

| Constant              | Default | Description                              |
|-----------------------|---------|------------------------------------------|
| `OBSTACLE_DISTANCE_CM`| 30     | Distance (cm) to trigger full stop       |
| `TURN_DISTANCE_CM`    | 50     | Distance (cm) to start slowing down      |
| `DRIVE_SPEED`          | 180    | PWM value for normal driving (0–255)     |
| `TURN_SPEED`           | 150    | PWM value during turns and slow approach |

## Project Structure

```
ultrasonic_robot/
├── ultrasonic_robot.ino    # Main sketch (setup/loop, obstacle logic)
├── motor_control.h         # Motor driver header
├── motor_control.cpp       # Motor driver implementation
├── ultrasonic_sensor.h     # Ultrasonic sensor header
├── ultrasonic_sensor.cpp   # Ultrasonic sensor implementation
└── README.md
```

## License

MIT — use freely for personal and educational projects.
