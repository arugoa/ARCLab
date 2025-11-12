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
int init_pos = 0;
int curr_pos = 0;
bool flip = false;

// Stabilizer Lock Servo
const int lockPWM = 3;
PWMServo lockServo;

// Buttons
unsigned long debounceDelay = 1000; // ms

// Clamp button
const int button1 = 26;
bool clampOn = true;
bool switchDir = false;

unsigned long lastDebounceTime1 = 0;
int reading1 = HIGH;
int lastButtonState1 = HIGH;

// Grip button
const int button2 = 27;
bool servoOn = true;

unsigned long lastDebounceTime2 = 0;
int reading2 = HIGH;
int lastButtonState2 = HIGH;


// Functions
