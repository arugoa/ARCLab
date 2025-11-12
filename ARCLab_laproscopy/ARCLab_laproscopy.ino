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
  gripServo.write(init_pos);

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
  unsigned long currentTime = millis();

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
      if (curr_pos > 0) {
        curr_pos -= 5;
      }

      gripServo.write(curr_pos);
    }
    else {
      if (curr_pos < 180) {
        curr_pos += 5;
      }

      gripServo.write(curr_pos);
    }
  } else {
    if (curr_pos > 90) {
      curr_pos -= 5;
    }
    else if (curr_pos < 90) {
      curr_pos += 5;
    }
    else {
      curr_pos = 90;
    }

    gripServo.write(curr_pos);
  }

  delay(50);
}