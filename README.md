# Smart-Seed-Sprayer-Robot
Arduino-based seed sprayer robot that uses keypad input to follow a grid-based field pattern and dispense seeds automatically.
## Project Overview
The Smart Seed Sprayer Robot is an Arduino-based automation system designed for small-scale agricultural applications. The robot follows a grid-based movement pattern defined by user input and dispenses seeds at fixed intervals using a servo mechanism.
## Features
- Keypad-based input for field dimensions
- Grid-based movement logic
- DC motor control using motor driver
- Servo-controlled seed dispensing
- I2C LCD for real-time status display
## Components Used
- Arduino Uno
- DC motors
- Motor driver (L298N / L293D)
- Servo motor
- 4x4 Keypad
- 16x2 I2C LCD
- Power supply
## How It Works
1. User enters field length and width using the keypad.
2. The values are displayed on the I2C LCD.
3. The robot moves in a grid-based pattern using DC motors.
4. At predefined points, the servo motor opens to dispense seeds.
5. The process continues until the entire field is covered.
