#include<Servo.h>

int in1R = 8;
int in2R = 9;
int ER = 11;
int in1L = 12;
int in2L = 13;
int EL = 6;
int echoRight = 4;
int trigRight = 5;
int echoFront = 2;
int trigFront = 3;
int FSRight = A2;
int FSCenter = A1;
int FSLeft = A0;
int rightSpeed = 255;
int leftSpeed = 120; // Lower Value accounts for difference in hardware motor speed

bool isFlame = false;

Servo swatterServo;

/* Performs swatting motion to extinguish flame
   Moves servo to maxAngle degrees, holds it extended for holdTime seconds,
   and returns it to the upright position, repeating this for the
   specified number of swats, with movement delay proportional to the angle
*/
void swat(Servo servo, int swatNumber, float holdTime, int maxAngle) {
  // Figures out movement delay
  int moveDelay = int(float(maxAngle) / float(180) * 1000);

  // Repeats swatting motion as specified by swatNumber
  for (int i = 0; i < swatNumber; i++) {
    servo.write(maxAngle);
    delay(moveDelay); // Wait for movement to complete
    delay(int(1000 * holdTime)); // Hold swatter over flame for hold seconds;
    servo.write(0);
    delay(moveDelay); // Wait for movement to complete
  }
}

/* Sends ultrasonic pulse out on specified pins and
  returns distance, along with timout for pulse in microseconds*/
int getUltrasonicDistance(int trigger, int echo, int timeout) {
  long duration;

  // Clears the trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  // Sends out pulse setting trigger to high for 10 microseconds
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Reads the echo pin, getting travel time
  duration = pulseIn(echo, HIGH, timeout);

  // Calculating distance
  return (duration * 0.034 / 2);
}

/* Moves L & R motors in a turn with a ratio between inside and outside
   pins on L298N driver are given to the method first
   dir --> true = forward, false = backward
   turn --> true = right, false = left
   ratio --> sets ratio between wheels for turn radius
   speed_percentage --> percentage of full speed
   time_delay --> how long the movement is held
*/
void moveRatioTurn(bool dir, bool turn, float speed_percentage, float ratio, int time_delay) {
  // Sets direction based on dir
  if (dir) {
    digitalWrite(in1R, LOW);
    digitalWrite(in1L, LOW);
    digitalWrite(in2R, HIGH);
    digitalWrite(in2L, HIGH);
  }
  else {
    digitalWrite(in1R, HIGH);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2R, LOW);
    digitalWrite(in2L, LOW);
  }

  // Sets movement speed
  if (turn) {
    analogWrite(ER, int(rightSpeed * speed_percentage * ratio));
    analogWrite(EL, int(leftSpeed * speed_percentage));
  }
  else {
    analogWrite(ER, int(rightSpeed * speed_percentage));
    analogWrite(EL, int(leftSpeed * speed_percentage * ratio));
  }

  // Sets duration of pulse
  delay(time_delay);

  // Stops movement, resetting PWM pins
  analogWrite(EL, 0);
  analogWrite(ER, 0);
}

/* Moves L & R motors in a turn with a ratio between inside and outside
   pins on L298N driver are given to the method first
   turn --> true = right, false = left
   speed_percentage --> percentage of full speed
   time_delay --> how long the movement is held
*/
void movePointTurn(bool turn, float speed_percentage, int time_delay) {
  // Sets direction based on turn
  if (turn) {
    digitalWrite(in1R, HIGH);
    digitalWrite(in1L, LOW);
    digitalWrite(in2R, LOW);
    digitalWrite(in2L, HIGH);
  }
  else {
    digitalWrite(in1R, LOW);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2R, HIGH);
    digitalWrite(in2L, LOW);
  }

  // Sets movement speed
  analogWrite(ER, int(rightSpeed * speed_percentage));
  analogWrite(EL, int(leftSpeed * speed_percentage));

  // Sets duration of pulse
  delay(time_delay);

  // Stops movement, resetting PWM pins
  analogWrite(EL, 0);
  analogWrite(ER, 0);
}

/* Moves L & R motors in a turn with a ratio between inside and outside
   pins on L298N driver are given to the method first
   dir --> true = forward, false = backward
   speed_percentage --> percentage of full speed
   time_delay --> how long the movement is held
*/
void moveStraight(bool dir, float speed_percentage, int time_delay) {
  // Sets direction based on dir (true = forward, false = backward)
  if (dir) {
    digitalWrite(in1R, LOW);
    digitalWrite(in1L, LOW);
    digitalWrite(in2R, HIGH);
    digitalWrite(in2L, HIGH);
  }
  else {
    digitalWrite(in1R, HIGH);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2R, LOW);
    digitalWrite(in2L, LOW);
  }

  // Sets movement speed
  analogWrite(ER, int(rightSpeed * speed_percentage));
  analogWrite(EL, int(leftSpeed * speed_percentage));

  // Sets duration of pulse
  delay(time_delay);

  // Stops movement, resetting PWM pins
  analogWrite(EL, 0);
  analogWrite(ER, 0);
}

/* Control scheme for when no flame is detected
   Turns left if a wall is detected in front (ultrasonic)
   Uses ratio turns to maintain distance from the right wall (ultrasonic)
*/
void wallControl(int minDistance, int maxDistance, int blankDistance) {
  int straightTime = 750;
  int turnTime = 300;

  int rightDistance = getUltrasonicDistance(trigRight, echoRight, 10000);
  int frontDistance = getUltrasonicDistance(trigFront, echoFront, 10000);
  Serial.print("Front distance: ");
  Serial.print(frontDistance);
  Serial.print("Right distance: ");
  Serial.println(rightDistance);

  // Checks for obstacle in front
  if (frontDistance > 15 || frontDistance == 0) {
    // Ensures robot has wall on right, not empty space
    if (rightDistance != 0 && rightDistance < blankDistance) {
      moveStraight(true, 1.0, straightTime);

      // Too close to wall, turns left
      if (rightDistance < minDistance) {
        moveRatioTurn(true, false, 1.0, 0.0, turnTime);
      }

      // Too far from wall, turns right
      else if (rightDistance > maxDistance) {
        moveRatioTurn(true, true, 1.0, 0.0, turnTime);
      }
    }
    // Empty space to the right, robot turns 90 degrees right
    else {
      moveRatioTurn(true, true, 1.0, 0.0, 1500);
      moveStraight(true, 1.0, 750);
    }
  }
  // Obstacle is in front
  else {
    moveRatioTurn(true, false, 1.0, 0.0, 1000);
  }


}

// Checks if there is a flame within the vicinity of the robot
bool checkForFlames() {
  if (analogRead(FSRight) < 500 || analogRead(FSCenter) < 500 || analogRead(FSLeft) < 500) {
    return true;
  }
  return false;
}


/* Moves robot to the flame source
   If the flame is on the left, robot ratio turns left until right detects it
   If the flame is on the right, robot ratio turns right until left detects it
   If the less sensitive center detects something, robot is close, and swatter is activated
*/
void flameControl() {
  int rightReading = analogRead(FSRight);
  int centerReading = analogRead(FSCenter);
  int leftReading = analogRead(FSLeft);

  // Flame is on the right
  if (rightReading < 500 && leftReading > 500) {
    // Waits for left sensor
    while (leftReading > 500) {
      moveRatioTurn(true, true, 1.0, 0.0, 5);
      leftReading = analogRead(FSLeft);
    }
  }

  // Flame is on the left
  else if (leftReading < 500 && rightReading > 500) {
    // Waits for right sensor
    while (rightReading > 500) {
      moveRatioTurn(true, false, 1.0, 0.0, 5);
      rightReading = analogRead(FSRight);
    }
  }

  // The flame is within swatting range
  else if (centerReading < 500 || (rightReading < 500 && leftReading < 500)) {
    swat(swatterServo, 4, 0.5, 15);
    delay(1000);
  }
}

void setup() {
  pinMode(FSRight, INPUT);
  pinMode(FSCenter, INPUT);
  pinMode(FSLeft, INPUT);
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  pinMode(ER, OUTPUT);
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(EL, OUTPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  swatterServo.attach(10);
  swatterServo.write(0); //Initialize servo to raised position

  // Initializing ultrasonics
  for (int i = 0; i < 5; i++) {
    getUltrasonicDistance(trigFront, echoFront, 10000);
    getUltrasonicDistance(trigRight, echoRight, 10000);
  }

  delay(3000); // Initial delay, minimum 850 to wait for servo
  Serial.begin(9600);
}

void loop() {
  //  // Checking for flames and making sure isFlame has not already been set
  //  if (!isFlame && checkForFlames()) {
  //    isFlame = true;
  //  }
  //  // Flame was detected, use flame control scheme
  //  if (isFlame) {
  //    flameControl();
  //  }
  //  // Flame not detected, use wall control
  //  else {
  //    wallControl(7, 12, 22);
  //  }

  wallControl(7, 12, 22);
  //flameControl();
}
