#include "main.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  FastLED.addLeds<NEOPIXEL, leftLED>(leftLeds, NUMLED);
  FastLED.addLeds<NEOPIXEL, rightLED>(rightLeds, NUMLED);
  FastLED.setBrightness(128);
  fill_solid(leftLeds, NUMLED, CRGB::Black);
  fill_solid(rightLeds, NUMLED, CRGB::Black);
  FastLED.show();

  // Left hand
  pinMode(laserL, OUTPUT);
  digitalWrite(laserL, LOW);
  gripServoL.attach(gripPWML);
  gripServoL.write(curr_grip_left);
  lockServoL.attach(lockPWML);
  lockServoL.write(curr_lock_left);

  // Right hand
  pinMode(laserR, OUTPUT);
  digitalWrite(laserR, LOW);
  gripServoR.attach(gripPWMR);
  gripServoR.write(curr_grip_right);
  lockServoR.attach(lockPWMR);
  lockServoR.write(curr_lock_right);

  // Buttons
  pinMode(laserButR, INPUT_PULLUP);
  pinMode(gripButR, INPUT_PULLUP);
  pinMode(lockButR, INPUT_PULLUP);

  pinMode(laserButL, INPUT_PULLUP);
  pinMode(gripButL, INPUT_PULLUP);
  pinMode(lockButL, INPUT_PULLUP);

  Serial.println("Ready for input");
}

void updateLEDs() {
  // -------- LEFT SIDE --------
  fill_solid(leftLeds, NUMLED, CRGB::Black);

  bool gripL = (curr_grip_left != 0);
  bool lockL = (curr_lock_left != 0);

  if (gripL) rightLeds[2] = CRGB::Blue;
  if (lockL) rightLeds[3] = CRGB::Green;

  // -------- RIGHT SIDE --------
  fill_solid(rightLeds, NUMLED, CRGB::Black);

  bool gripR = (curr_grip_right != 0);
  bool lockR = (curr_lock_right != 0);

  if (gripR) rightLeds[0] = CRGB::Blue;
  if (lockR) rightLeds[1] = CRGB::Green;


  FastLED.show();
}

void handleButtons() {
  unsigned long now = millis();
  if (now - lastButtonTime < debounceDelay) return;

  // ----- RIGHT HAND -----
  if (digitalRead(gripButR) == LOW) {       // Grip toggle
    des_grip_right = (des_grip_right == 0) ? grip_limit : 0;
    lastButtonTime = now;
  }

  if (digitalRead(lockButR) == LOW) {       // Lock toggle
    des_lock_right = (des_lock_right == 0) ? grip_limit : 0;
    lastButtonTime = now;
  }

  if (digitalRead(laserButR) == LOW) {      // Laser toggle
    laserROn = !laserROn;
    lastButtonTime = now;
  }

  // ----- LEFT HAND -----
  if (digitalRead(gripButL) == LOW) {       // Grip toggle
    des_grip_left = (des_grip_left == 0) ? grip_limit : 0;
    lastButtonTime = now;
  }

  if (digitalRead(lockButL) == LOW) {       // Lock toggle
    des_lock_left = (des_lock_left == 0) ? grip_limit : 0;
    lastButtonTime = now;
  }

  if (digitalRead(laserButL) == LOW) {      // Laser toggle
    laserLOn = !laserLOn;
    lastButtonTime = now;
  }
}


void loop() {
  currentTime = millis();

  handleButtons();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    char armID = input.charAt(0);

    if (armID == 'R') {
      int angle = input.substring(1).toInt();
      angle = constrain(angle, 0, grip_limit);
      des_grip_right = angle;
    } 
    else if (armID == 'L') {
      int angle = input.substring(1).toInt();
      angle = constrain(angle, 0, grip_limit);
      des_grip_left = angle;
    }
    else if (armID == 'C') {
      if (input.charAt(1) == 'L') {
        int angle = input.substring(2).toInt();
        des_lock_left = angle;
      }
      else if (input.charAt(1) == 'R') {
        int angle = input.substring(2).toInt();
        des_lock_right = angle;
      }
    }

    digitalWrite(LED, LOW);
  } 
  else {
    digitalWrite(LED, HIGH);  // blink if idle
  }

  // control the motors
  if (curr_grip_left > des_grip_left) curr_grip_left -= 5;
  else if (curr_grip_left < des_grip_left) curr_grip_left += 5;
  gripServoL.write(curr_grip_left);
  
  if (curr_lock_left > des_lock_left) curr_lock_left -= 1;
  else if (curr_lock_left < des_lock_left) curr_lock_left += 1;
  lockServoL.write(curr_lock_left);

  if (curr_grip_right > des_grip_right) curr_grip_right -= 5;
  else if (curr_grip_right < des_grip_right) curr_grip_right += 5;
  gripServoR.write(curr_grip_right);
  
  if (curr_lock_right > des_lock_right) curr_lock_right -= 1;
  else if (curr_lock_right < des_lock_right) curr_lock_right += 1;
  lockServoR.write(curr_lock_right);
  

  if (laserLOn) digitalWrite(laserL, HIGH);
  else digitalWrite(laserL, LOW);

  if (laserROn) digitalWrite(laserR, HIGH);
  else digitalWrite(laserR, LOW);

  updateLEDs();

  int elapsed = millis() - currentTime;
  if (elapsed < loopTime) delay(loopTime - elapsed);
}