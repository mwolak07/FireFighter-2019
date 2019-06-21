int in1R = 8;
int in2R = 9;
int ER = 11;
int in1L = 12;
int in2L = 13;
int EL = 6;
int rightSpeed = 255; // Account for differences in motor speed
int leftSpeed = 145;

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

void setup() {
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  pinMode(ER, OUTPUT);
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(EL, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  Serial.println("Forward 100%");
  moveStraight(false, 1.0, 2000);

//  Serial.println("Backward 100%");
//  moveStraight(false, 1.0, 2000);
//  delay(1000);
//  
//  Serial.println("Right Point Turn 100%");
//  movePointTurn(true, 1.0, 2000);
//  delay(1000);
//  
//  Serial.println("Left Point Turn 100%");
//  movePointTurn(false, 1.0, 2000);
//  delay(1000);
//  
//  Serial.println("Right 50% Ratio Turn 100% forward");
//  moveRatioTurn(true, true, 1.0, 0.5, 2000);
//  delay(1000);
//  
//  Serial.println("Left 50% Ratio Turn 100% forward");
//  moveRatioTurn(true, false, 1.0, 0.5, 2000);
//  delay(1000);
//  
//  Serial.println("Right 50% Ratio Turn 100% backward");
//  moveRatioTurn(false, true, 1.0, 0.5, 2000);
//  delay(1000);
//  
//  Serial.println("Left 50% Ratio Turn 100% backward");
//  moveRatioTurn(false, false, 1.0, 0.5, 2000);
//  delay(1000);
  
}
