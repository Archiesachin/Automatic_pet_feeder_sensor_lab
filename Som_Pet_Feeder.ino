#include <Servo.h>

int pos = 0; 
const int trigPin = 9;
const int echoPin = 10;
Servo myservo;
float duration, distance;
int touchState = LOW;
int currentState; 
const int TOUCH_PIN = 4;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.attach(7);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TOUCH_PIN, INPUT_PULLUP); // Set touch pin as input with internal pull-up resistor
  
}

void loop() {
  // Ultrasonic Sensor Part
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  // Touch Sensor Part
  currentState = digitalRead(TOUCH_PIN);

  // Logic for activating servo if pet is detected or touch sensor is triggered
  if (distance <= 15 || (touchState == LOW && currentState == HIGH)) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Pet Detected");
    myservo.write(180);
    delay(3000);
    myservo.write(0);
                    
    for (pos = 0; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(10);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(1);
    }
  } 
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Clear ");
    myservo.write(0);
    delay(50);
  }

  // Update touch sensor state
  touchState = currentState;

  delay(100);
}
