int EchoRight = 2;
int TrigRight = 3;
int EchoFront = 4;
int TrigFront = 5;

/* Sends ultrasonic pulse out on specified pins and
returns distance */
int ultrasonicPulse(int trigger, int echo) {
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
  pinMode(TrigRight, OUTPUT);
  pinMode(EchoRight, INPUT);
  pinMode(TrigFront, OUTPUT);
  pinMode(EchoFront, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Front distance: ");
  Serial.print(ultrasonicPulse(TrigFront, EchoFront));
  Serial.print("    Right distance: ");
  Serial.println(ultrasonicPulse(TrigRight, EchoRight));
}
