// Motor Pinouts

#include <Servo.h>

Servo myServo;

// Clamp to connect to the tool
const int clampCW = 7;
const int clampCCW = 6;
const int clampButton = 8;

// Open and close gripper
const int gripPWM = 2;

// Lock and unlock position
const int lockPWM = 3;

// LEDs for debugging
const int LED = 13;

// button
const int button1 = 26;
bool click = true;
bool hold = false;

const int button2 = 27;

void setup() {
  // Testing LED
  pinMode(LED, OUTPUT);

  // Clamp Screw motor
  pinMode(clampCW, OUTPUT);
  pinMode(clampCCW, OUTPUT);

  // Grip motor
  pinMode(gripPWM, OUTPUT);

  // Set up buttons
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

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
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);   // set the LED on
  if (digitalRead(button1) == HIGH){
    Serial.println("Button 1 on");
  }

  if (digitalRead(button2) == HIGH){
    Serial.println("Button 2 on");
  }

  // Turn clockwise
  digitalWrite(clampCW, HIGH);
  digitalWrite(clampCCW, LOW);
  
  analogWrite(gripPWM, 100);

  delay(1000);                  // wait for a second
  
  digitalWrite(LED, LOW);    // set the LED off
  
  // Turn counter clockwise
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, HIGH);  

  analogWrite(gripPWM, 0);

  delay(1000);                  // wait for a second
  
  // Turn off
  digitalWrite(clampCW, LOW);
  digitalWrite(clampCCW, LOW);
}
