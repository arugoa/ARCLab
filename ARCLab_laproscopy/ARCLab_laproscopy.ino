#include <PWMServo.h>

// Motor Pinouts

// Clamp to connect to the tool
const int clampCW = 7;
const int clampCCW = 6;
const int clampButton = 8;

// Open and close gripper
const int gripPWM = 2;
PWMServo gripServo;

// Lock and unlock position
const int lockPWM = 3;

// LEDs for debugging
const int LED = 13;

// button
const int button1 = 26;
bool click = true;
bool hold = false;

const int button2 = 27;
bool servoOn = true;
bool lastButton = HIGH;

void setup() {
  // Testing LED
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Clamp Screw motor
  pinMode(clampCW, OUTPUT);
  pinMode(clampCCW, OUTPUT);

  // Grip motor
  gripServo.attach(gripPWM);
  gripServo.write(0);

  // Set up buttons
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  // Init motors to LOW
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, LOW);
}

void button_logic() {
  // if clicked for a lil bit, turn off/on
  if (digitalRead(button1) == HIGH) {
    click = !click;
    delay(500);
    // if click is held for half a second, switch ccw and cw
    if (digitalRead(button1) == HIGH) {
      click = !click;
      hold = !hold;
    }
  }
}

void loop() {
  bool button = digitalRead(button2);
  // put your main code here, to run repeatedly:
  

  if (lastButton == HIGH && button == LOW) {
    servoOn = !servoOn;
  }

  for (int pos = 0; pos <= 180; pos += 5) {
    gripServo.write(pos);
    delay(100);
  }

  // Sweep back
  for (int pos = 180; pos >= 0; pos -= 5) {
    gripServo.write(pos);
    delay(100);
  }

  digitalWrite(LED, HIGH);   // set the LED on

  // Turn clockwise
  digitalWrite(clampCW, HIGH);
  digitalWrite(clampCCW, LOW);
  delay(1000);                  // wait for a second
  
  digitalWrite(LED, LOW);    // set the LED off
  
  // Turn counter clockwise
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, HIGH);  
  delay(1000);                  // wait for a second
  
  // Turn off
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, LOW);
}
