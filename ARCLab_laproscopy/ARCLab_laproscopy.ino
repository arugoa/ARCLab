#include "main.h"

void setup() {
  // Begin Serial output
  Serial.begin(115200);
  
  // Initializing LEDs
  pinMode(LED, OUTPUT);

  // Clamp Screw motor
  pinMode(clampCW, OUTPUT);
  pinMode(clampCCW, OUTPUT);

  // Grip servo + init
  gripServo.attach(gripPWM);
  gripServo.write(init_grip);

  // Lock servo + init
  lockServo.attach(lockPWM);
  lockServo.write(init_lock);

  // Set up buttons
  pinMode(button1, INPUT_PULLUP);
  delayMicroseconds(10);
  pinMode(button2, INPUT_PULLUP);
  delayMicroseconds(10);

  // Init motors to LOW
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, LOW);
}


void loop() {
  reading1 = digitalRead(button1);
  reading2 = digitalRead(button2);
  currentTime = millis();

  button_logic();

  control_logic();

  delay(50);
}