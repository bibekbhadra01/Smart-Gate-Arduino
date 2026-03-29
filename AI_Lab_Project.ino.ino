#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

Servo myServo;

long duration;
float distance;

int currentPos = 140;   // Start position (closed)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(currentPos);

  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // OPEN GATE
  if (distance < 30) {
    Serial.println("Opening...");
    
    for (int pos = currentPos; pos <= 180; pos++) {
      myServo.write(pos);
      delay(15);
    }
    currentPos = 180;
  } 

  // CLOSE GATE
  else {
    Serial.println("Closing...");
    
    for (int pos = currentPos; pos >= 140; pos--) {
      myServo.write(pos);
      delay(15);
    }
    currentPos = 140;
  }

  delay(300);
}