// ========================================
// Four DC Motors Control using L293D
// ========================================

// Enable pins - PWM speed control
const int ENA = 5;
const int ENB = 6;

// Direction control pins
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 10;
const int IN4 = 9;

// Motor speed (0 - 255)
const int motorSpeed = 180;

void setup() {

  // Configure all pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set motor speed
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void loop() {

  // ========================================
  // 1. Move Forward for 30 seconds
  // ========================================
  forward();
  delay(30000);

  stopMotors();
  delay(1000);


  // ========================================
  // 2. Move Backward for 60 seconds
  // ========================================
  backward();
  delay(60000);

  stopMotors();
  delay(1000);


  // ========================================
  // 3. Alternate Right and Left for 60 sec
  // ========================================

  // Each cycle = 5 sec Right + 5 sec Left
  // 6 cycles = 60 seconds

  for (int i = 0; i < 6; i++) {

    turnRight();
    delay(5000);

    turnLeft();
    delay(5000);
  }


  // Stop before repeating the sequence
  stopMotors();
  delay(2000);
}


// ========================================
// Movement Functions
// ========================================

// Move Forward
void forward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// Move Backward
void backward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// Turn Right
void turnRight() {

  // First motor group → Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Second motor group → Backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// Turn Left
void turnLeft() {

  // First motor group → Backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Second motor group → Forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// Stop all motors
void stopMotors() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
