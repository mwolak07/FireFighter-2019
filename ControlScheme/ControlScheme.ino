#include<Servo.h>

int in1Right = 8;
int in2Right = 9;
int enableRight = 11;
int in1Left = 12;
int in2Left = 13;
int enableLeft = 6;
int echoRight = 4;
int trigRight = 5;
int echoFront = 2;
int trigFront = 3;
int FSRight = A2;
int FSCenter = A1;
int FSLeft = A0;
Servo swatterServo;

/* Performs swatting motion to extinguish flame
   Moves servo to maxAngle degrees, holds it extended for holdTime seconds,
   and returs it to the upright position, repeating this for the
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
void moveRatioTurn(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool dir, bool turn, float speed_percentage, float ratio, int time_delay) {
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
    analogWrite(ER, int(255 * speed_percentage * ratio));
    analogWrite(EL, int(255 * speed_percentage));
  }
  else {
    analogWrite(ER, int(255 * speed_percentage));
    analogWrite(EL, int(255 * speed_percentage * ratio));
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
void movePointTurn(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool turn, float speed_percentage, int time_delay) {
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
  analogWrite(ER, int(255 * speed_percentage));
  analogWrite(EL, int(255 * speed_percentage));

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
void moveStraight(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool dir, float speed_percentage, int time_delay) {
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
  analogWrite(ER, int(255 * speed_percentage));
  analogWrite(EL, int(255 * speed_percentage));

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
void initialControl(int minDistance, int maxDistance, int blankDistance) {
  // Initial ultrasonic sensor values
  int frontDistance = getUltrasonicDistance(trigFront, echoFront, 10000);
  int rightDistance = getUltrasonicDistance(trigRight, echoRight, 10000);
  Serial.println(rightDistance);

  // Ensures ultrasonics aren't timing out
  if(rightDistance !=0 && rightDistance < blankDistance) {
    // Robot too close to the wall, goes left
    if(rightDistance < minDistance) {
      moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, 1.0, 0.4, 150); // Turn out
      // Moves away until distance is correct
      while(rightDistance < minDistance) {
        moveStraight(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 10);
        rightDistance = getUltrasonicDistance(trigRight, echoRight, 10000);
        Serial.println(rightDistance);
      }
      moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 0.4, 150); // Strighten out
    }

    // Robot too far from the wall, goes right
    else if(rightDistance > maxDistance) {
      moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 0.4, 150); // Turn in
      // Moves away until distance is correct
      while(rightDistance > maxDistance) {
        moveStraight(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 10);
        rightDistance = getUltrasonicDistance(trigRight, echoRight, 10000);
        Serial.println(rightDistance);
      }
      moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, 1.0, 0.4, 150); // Strighten out
    }

    // Goes straight if everything is OK
    else {
      moveStraight(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 10);
    }
  }
}

void setup() {
  pinMode(FSRight, INPUT);
  pinMode(FSCenter, INPUT);
  pinMode(FSLeft, INPUT);
  pinMode(in1Right, OUTPUT);
  pinMode(in2Right, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(in1Left, OUTPUT);
  pinMode(in2Left, OUTPUT);
  pinMode(enableLeft, OUTPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  swatterServo.attach(10);
  swatterServo.write(0); //Initialize servo to raised position
  delay(850);
  Serial.begin(9600);
}

void loop() {
  initialControl(10, 20, 30);
}
