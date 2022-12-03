
int trigPin = 2;
int echoPin = 3;
int Buzzer = 7;
#include <Servo.h>

Servo servo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(9);
  pos = 0;
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration)/29.1;
  duration = pulseIn(echoPin, LOW);
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print("\n");
  delay(0);
  if (distance <= 400){
    digitalWrite(Buzzer, HIGH);
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degreesi
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    digitalWrite(Buzzer, LOW);
  }
}
