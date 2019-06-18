int in1Right = 8;
int in2Right = 9;
int enableRight = 11;
int in1Left = 12;
int in2Left = 13;
int enableLeft = 6;

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

void setup() {
  pinMode(in1Right, OUTPUT);
  pinMode(in2Right, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(in1Left, OUTPUT);
  pinMode(in2Left, OUTPUT);
  pinMode(enableLeft, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  Serial.println("Forward 100%");
  moveStraight(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 0.75, 2000);
  delay(1000);
  
  Serial.println("Backward 100%");
  moveStraight(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, 1.0, 2000);
  delay(1000);
  
  Serial.println("Right Point Turn 100%");
  movePointTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, 1.0, 2000);
  delay(1000);
  
  Serial.println("Left Point Turn 100%");
  movePointTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, 1.0, 2000);
  delay(1000);
  
  Serial.println("Right 50% Ratio Turn 100% forward");
  moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, true, 0.5, 1.0, 2000);
  delay(1000);
  
  Serial.println("Left 50% Ratio Turn 100% forward");
  moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, true, false, 0.5, 1.0, 2000);
  delay(1000);
  
  Serial.println("Right 50% Ratio Turn 100% backward");
  moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, true, 0.5, 1.0, 2000);
  delay(1000);
  
  Serial.println("Left 50% Ratio Turn 100% backward");
  moveRatioTurn(in1Right, in2Right, enableRight, in1Left, in2Left, enableLeft, false, false, 0.5, 1.0, 2000);
  delay(1000);
  
}
