int echoRight = 2;
int trigRight = 3;
int echoFront = 4;
int trigFront = 5;

/* Sends ultrasonic pulse out on specified pins and
returns distance */
int getUltrasonicDistance(int trigger, int echo) {
  long duration;
  
  // Clears the trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  // Sends out pulse setting trigger to high for 10 microseconds
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Reads the echo pin, getting travel time
  duration = pulseIn(echo, HIGH);

  // Calculating distance
  return (duration*0.034/2);
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
  Serial.print(ultrasonicPulse(trigFront, echoFront));
  Serial.print("    Right distance: ");
  Serial.println(ultrasonicPulse(trigRight, echoRight));
}
