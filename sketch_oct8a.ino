#include <Servo.h>

Servo myServo;

int ldrPin = A0;        // LDR connected to A0
int servoPin = 9;       // Servo signal on pin 9
int threshold = 500;    // Adjust based on light level
int ldrValue=0;
bool actionDone = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(90);    // Start at middle position
}

void loop() {
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  // When dark detected, do 3 back-and-forth sweeps
  if (ldrValue < threshold && !actionDone) {
    Serial.println("Dark detected — moving servo 3 cycles");

    for (int i = 0; i < 3; i++) {
      // Clockwise
      myServo.write(180);
      delay(800);  // Adjust speed (depends on servo)
      
      // Anticlockwise
      myServo.write(0);
      delay(800);
    }

    // Return to middle and stop
    myServo.write(90);
    Serial.println("Movement complete.");
    actionDone = true;
  }

  // Reset when bright again
  if (ldrValue > threshold + 50) {
    actionDone = false;
  }

  delay(200);
}
