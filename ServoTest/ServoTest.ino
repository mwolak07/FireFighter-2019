#include <Servo.h>

Servo swatterServo;

/* Performs swatting motion to extinguish flame
 * Moves servo to maxAngle degrees, holds it extended for holdTime seconds,
 * and returs it to the upright position, repeating this for the 
 * specified number of swats, with movement delay proportional to the angle
 */
void swat(Servo servo, int swatNumber, float holdTime, int maxAngle) {
  // Figures out movement delay
  int moveDelay = int(float(maxAngle)/float(180)*850);
  
  // Repeats swatting motion as specified by swatNumber
  for(int i=0; i < swatNumber; i++) {
    servo.write(maxAngle);
    delay(moveDelay); // Wait for movement to complete
    delay(int(1000*holdTime)); // Hold swatter over flame for hold seconds;
    servo.write(0); 
    delay(moveDelay); // Wait for movement to complete
  }
}

void setup() {
  swatterServo.attach(10);
  swatterServo.write(0); //Initialize servo to raised position
  Serial.begin(9600);
}

void loop() {
  Serial.println("Swatting 4 times");
  swat(swatterServo, 4, 0.5, 100);
  delay(2000);
}
