int FSRight = A0;
int FSCenter = A1;
int FSLeft = A2;

void setup() {
  Serial.begin(9600);
  pinMode(FSRight, INPUT);
  pinMode(FSCenter, INPUT);
  pinMode(FSLeft, INPUT);
}

void loop() {
  Serial.print("Flame sensor right: ");
  Serial.print(analogRead(FSRight));
  Serial.print("    Flame sensor center: ");
  Serial.print(analogRead(FSCenter));
  Serial.print("    Flame sensor left: ");
  Serial.println(analogRead(FSLeft));
}
