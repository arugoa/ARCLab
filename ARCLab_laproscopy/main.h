#include <PWMServo.h>


// LEDs for debugging
const int LED = 13;


// Motor Pinouts
// Clamp motor
const int clampCCW = 6;
const int clampCW = 7;

// Gripper Servo
const int gripPWM = 2;
PWMServo gripServo;
int init_grip = 0;
int curr_grip = 0;
bool flip_grip = false;

// Stabilizer Lock Servo
const int lockPWM = 3;
PWMServo lockServo;
int init_lock = 0;
int curr_lock = 0;
bool flip_lock = false;

// Buttons
unsigned long debounceDelay = 1000; // ms
unsigned long currentTime = 0;

// Clamp button
const int button1 = 26;
bool clampOn = true;
bool switchDir = false;

// logic vars
unsigned long lastDebounceTime1 = 0;
int reading1 = HIGH;
int lastButtonState1 = HIGH;

// Grip button
const int button2 = 27;
bool servoOn = true;
bool flip = false;

// logic vars
unsigned long lastDebounceTime2 = 0;
int reading2 = HIGH;
int lastButtonState2 = HIGH;


// Functions
void button_logic() {
  // --- Clamp Button ---
  if (reading1 == LOW && lastButtonState1 == HIGH) {
    switchDir = !switchDir;
    lastDebounceTime1 = currentTime;
  }

  if (reading1 == HIGH && lastButtonState1 == LOW) {
    if (currentTime - lastDebounceTime1 > debounceDelay) {
      clampOn = !clampOn;
    }
  }
  lastButtonState1 = reading1;

  // --- Servo Button ---
  if (reading2 == LOW && lastButtonState2 == HIGH) {
    flip = !flip;
    lastDebounceTime2 = currentTime;
  }

  if (reading2 == HIGH && lastButtonState2 == LOW) {
    if (currentTime - lastDebounceTime2 > debounceDelay) {
      servoOn = !servoOn;
    }
  }
  lastButtonState2 = reading2;
}

void control_logic() {
  // --- Control Logic ---
  if (clampOn) {
    if (switchDir) {
      digitalWrite(clampCW, LOW);
      digitalWrite(clampCCW, HIGH);
    }
    else {
      digitalWrite(clampCW, HIGH);
      digitalWrite(clampCCW, LOW);
    }
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(clampCW, LOW);
    digitalWrite(clampCCW, LOW);
    digitalWrite(LED, LOW);
  }

  if (servoOn) {
    if (flip) {
      // Use grip servo
      if (flip_grip) curr_grip -= 5; 
      else curr_grip += 5; 
      
      if (curr_grip >= 180 || curr_grip <= 0) { 
        flip_grip = !flip_grip; 
      }

      gripServo.write(curr_grip);
    }
    else {
      // Use grip servo
      if (flip_lock) curr_lock -= 5; 
      else curr_lock += 5; 
      
      if (curr_lock >= 180 || curr_lock <= 0) { 
        flip_lock = !flip_lock; 
      }

      lockServo.write(curr_lock);
    }
  }
}