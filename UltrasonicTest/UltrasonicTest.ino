int echoRight = 4;
int trigRight = 5;
int echoFront = 2;
int trigFront = 3;

/* Sends ultrasonic pulse out on specified pins and
  returns distance, along with timeout for pulse in microseconds */
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

void setup() {
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Front distance: ");
  Serial.print(getUltrasonicDistance(trigFront, echoFront, 10000));
  Serial.print("    Right distance: ");
  Serial.println(getUltrasonicDistance(trigRight, echoRight, 10000));
}
