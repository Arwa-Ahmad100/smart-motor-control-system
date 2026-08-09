#include <Servo.h>

Servo headServo;

// ===============================
// Pin Configuration
// ===============================

// Ultrasonic Sensor
const int echoPin = 3;
const int trigPin = 4;

// L293D Enable Pins
const int ENA = 5;
const int ENB = 6;

// L293D Direction Pins
const int IN1 = 7;
const int IN2 = 8;
const int IN4 = 9;
const int IN3 = 10;

// Servo Motor
const int servoPin = 11;

// ===============================
// Settings
// ===============================

const int motorSpeed = 180;
const int obstacleDistance = 10;

const int CENTER = 90;
const int RIGHT  = 30;
const int LEFT   = 150;


// ===============================
// Setup
// ===============================

void setup() {

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // L293D
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Servo
  headServo.attach(servoPin);
  headServo.write(CENTER);

  // Motor speed
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  Serial.begin(9600);

  delay(1000);
}


// ===============================
// Main Program
// ===============================

void loop() {

  // Measure distance in front
  float frontDistance = readDistance();

  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.println(" cm");

  // --------------------------------
  // No obstacle → Move forward
  // --------------------------------

  if (frontDistance > obstacleDistance) {

    headServo.write(CENTER);
    forward();
  }

  // --------------------------------
  // Obstacle detected
  // --------------------------------

  else {

    // Stop immediately
    stopMotors();
    delay(500);

    // ===============================
    // Look Right
    // ===============================

    headServo.write(RIGHT);
    delay(1000);

    float rightDistance = readDistance();

    Serial.print("Right: ");
    Serial.print(rightDistance);
    Serial.println(" cm");


    // ===============================
    // Look Left
    // ===============================

    headServo.write(LEFT);
    delay(1000);

    float leftDistance = readDistance();

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.println(" cm");


    // ===============================
    // Return Head to Center
    // ===============================

    headServo.write(CENTER);
    delay(500);


    // ===============================
    // Choose Clearer Direction
    // ===============================

    if (rightDistance > leftDistance) {

      Serial.println("Turning RIGHT");

      turnRight();
      delay(1200);
    }

    else {

      Serial.println("Turning LEFT");

      turnLeft();
      delay(1200);
    }


    // Stop after turning
    stopMotors();
    delay(500);
  }
}


// ===============================
// Ultrasonic Distance Measurement
// ===============================

float readDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  // No echo received
  if (duration == 0) {
    return 999;
  }

  float distance = duration * 0.0343 / 2;

  return distance;
}


// ===============================
// Move Forward
// ===============================

void forward() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// ===============================
// Turn Right
// ===============================

void turnRight() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  // Left side forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right side backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// ===============================
// Turn Left
// ===============================

void turnLeft() {

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);

  // Left side backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right side forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// ===============================
// Stop Motors
// ===============================

void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
