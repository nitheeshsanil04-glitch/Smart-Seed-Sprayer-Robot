/*
 Smart Seed Sprayer Robot
 Author: Nitheesh
 Description:
 Arduino-based robot that uses keypad input to control grid-based
 movement and servo-controlled seed dispensing.
*/

#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo motor
Servo seedServo;

// Motor driver pins
int m1a = 8;
int m1b = 9;
int m2a = 10;
int m2b = 11;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {A0,A1,A2,A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables
String input = "";
int fieldLength = 0;
int fieldWidth = 0;
bool lengthEntered = false;

void setup() {
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  seedServo.attach(6);
  seedServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.print("Enter Length:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input);
    }

    if (key == '#') {
      if (!lengthEntered) {
        fieldLength = input.toInt();
        input = "";
        lengthEntered = true;
        lcd.clear();
        lcd.print("Enter Width:");
      } else {
        fieldWidth = input.toInt();
        lcd.clear();
        lcd.print("Starting...");
        delay(2000);
        startSpraying();
      }
    }
  }
}

void startSpraying() {
  for (int row = 0; row < fieldWidth; row++) {
    moveForward();
    delay(fieldLength * 1000);
    stopMotors();

    dispenseSeed();
    delay(500);

    turnRight();
    delay(700);
    stopMotors();
  }

  lcd.clear();
  lcd.print("Task Completed");
}

void moveForward() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

void turnRight() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}

void stopMotors() {
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}

void dispenseSeed() {
  seedServo.write(90);
  delay(300);
  seedServo.write(0);
}

