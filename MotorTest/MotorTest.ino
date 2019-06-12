int In1Right = 8;
int In2Right = 9;
int EnableRight = 6;
int In1Left = 12;
int In2Left = 13;
int EnableLeft = 11;

/* Moves L & R motors in a turn with a ratio between inside and outside
 * pins on L298N driver are given to the method first
 * dir --> true = forward, false = backward
 * turn --> true = right, false = left
 * ratio --> sets ratio between wheels for turn radius
 * speed_percentage --> percentage of full speed
 * time_delay --> how long the movement is held
 */
void moveRatioTurn(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool dir, bool turn, float ratio, float speed_percentage, int time_delay) {
  // Sets direction based on dir
  if(dir) {
    digitalWrite(in1R, HIGH);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2R, LOW);
    digitalWrite(in2L, LOW);
  }
  else {
    digitalWrite(in1R, LOW);
    digitalWrite(in1L, LOW);
    digitalWrite(in2R, HIGH);
    digitalWrite(in2L, HIGH);
  }

  // Sets movement speed
  if(turn) {
    analogWrite(ER, int(255*speed_percentage*ratio));
    analogWrite(EL, int(255*speed_percentage));
  }
  else {
    analogWrite(ER, int(255*speed_percentage));
    analogWrite(EL, int(255*speed_percentage*ratio));
  }
  
  // Sets duration of pulse
  delay(time_delay);
}

/* Moves L & R motors in a turn with a ratio between inside and outside
 * pins on L298N driver are given to the method first
 * turn --> true = right, false = left
 * speed_percentage --> percentage of full speed
 * time_delay --> how long the movement is held
 */
void movePointTurn(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool turn, float speed_percentage, int time_delay) {
  // Sets direction based on dir
  if(turn) {
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
  analogWrite(ER, int(255*speed_percentage));
  analogWrite(EL, int(255*speed_percentage));
  
  // Sets duration of pulse
  delay(time_delay);
}

/* Moves L & R motors in a turn with a ratio between inside and outside
 * pins on L298N driver are given to the method first
 * dir --> true = forward, false = backward
 * speed_percentage --> percentage of full speed
 * time_delay --> how long the movement is held
 */
void moveStrait(int in1R, int in2R, int ER, int in1L, int in2L, int EL, bool dir, float speed_percentage, int time_delay) {
  // Sets direction based on dir
  if(dir) {
    digitalWrite(in1R, HIGH);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2R, LOW);
    digitalWrite(in2L, LOW);
  }
  else {
    digitalWrite(in1R, LOW);
    digitalWrite(in1L, LOW);
    digitalWrite(in2R, HIGH);
    digitalWrite(in2L, HIGH);
  }

  // Sets movement speed
  analogWrite(ER, int(255*speed_percentage));
  analogWrite(EL, int(255*speed_percentage));
  
  // Sets duration of pulse
  delay(time_delay);
}

void setup() {
  pinMode(In1Right, OUTPUT);
  pinMode(In2Right, OUTPUT);
  pinMode(EnableRight, OUTPUT);
  pinMode(In1Left, OUTPUT);
  pinMode(In2Left, OUTPUT);
  pinMode(EnableLeft, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Forward 50%");
  moveStrait(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, 0.5, 500);
  Serial.println("Forward 100%");
  moveStrait(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, 1.0, 500);
  Serial.println("Backward 50%");
  moveStrait(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, 0.5, 500);
  Serial.println("Backward 100%");
  moveStrait(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, 1.0, 500);
  Serial.println("Right Point Turn 50%");
  movePointTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, 0.5, 500);
  Serial.println("Right Point Turn 100%");
  movePointTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, 1.0, 500);
  Serial.println("Left Point Turn 50%");
  movePointTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, 0.5, 500);
  Serial.println("Left Point Turn 100%");
  movePointTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, 1.0, 500);
  Serial.println("Right 50% Ratio Turn 100% forward");
  moveRatioTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, true, 0.5, 1.0, 500);
  Serial.println("Left 50% Ratio Turn 100% forward");
  moveRatioTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, true, false, 0.5, 1.0, 500);
  Serial.println("Right 50% Ratio Turn 100% backward");
  moveRatioTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, true, 0.5, 1.0, 500);
  Serial.println("Left 50% Ratio Turn 100% backward");
  moveRatioTurn(In1Right, In2Right, EnableRight, In1Left, In2Left, EnableLeft, false, false, 0.5, 1.0, 500);
}
