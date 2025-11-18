#include <PWMServo.h>
#include <FastLED.h>

// LEDs for debugging
const int LED = 13;

const int NUMLED = 5;
const int rightLED = 21;
const int leftLED = 20;
CRGB leftLeds[NUMLED];
CRGB rightLeds[NUMLED];

int leftRGB[] = {0, 0, 0, 0};   // [R, G, B, W]
int rightRGB[] = {0, 0, 0, 0};  // [R, G, B, W]

int currentTime = 0;
const int loopTime = 10;


const int grip_limit = 50;

// Motor Pinouts

// Left Arm
// laser motor
const int laserL = 27;
bool laserLOn = false;
// Gripper Servo
const int gripPWML = 4;
PWMServo gripServoL;
int des_grip_left = 0;
int curr_grip_left = 0;
// Stabilizer Lock Servo
const int lockPWML = 5;
PWMServo lockServoL;
int des_lock_left = 0;
int curr_lock_left = 0;

// Right Arm
// laser motor
const int laserR = 26;
bool laserROn = false;
// Gripper Servo
const int gripPWMR = 2;
PWMServo gripServoR;
int des_grip_right = 0;
int curr_grip_right = 0;
// Stabilizer Lock Servo
const int lockPWMR = 3;
PWMServo lockServoR;
int des_lock_right = 0;
int curr_lock_right = 0;


// Buttons
// Right hand
const int laserButR = 16;
const int gripButR = 41;
const int lockButR = 17;

// Left hand
const int laserButL = 32;
const int gripButL = 31;
const int lockButL = 10;

// Debounce timing
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 150; // ms