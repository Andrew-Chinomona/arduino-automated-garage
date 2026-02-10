#include <IRremote.h>

const int buzzerPin = 10;     // Buzzer pin
const int trigPin = 34;       // Ultrasonic trigger pin
const int echoPin = 35;       // Ultrasonic echo pin
const int buttonPin = 33;     // Button pin
const int irPin = 3;          // IR transmitter pin
const unsigned int irSignal[] = {900, 450, 900, 450, 900, 450, 900, 450, 900, 450}; // IR signal pattern

IRsend irsend;
int distance;
long duration;

void setup() {
  pinMode(trigPin, OUTPUT);        // Set trigger pin as OUTPUT
  pinMode(echoPin, INPUT);         // Set echo pin as INPUT
  pinMode(buzzerPin, OUTPUT);      // Set buzzer pin as OUTPUT
  pinMode(buttonPin, INPUT_PULLUP);// Set button pin as INPUT with pull-up
  irsend.begin(irPin);             // Initialize IR transmitter
}

int checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Measure the echo time
  distance = duration * 0.034 / 2;   // Convert to distance in cm
  return distance;
}

void loop() {
  // Check distance and control buzzer
  distance = checkDistance();
  if (distance < 15) { 
    analogWrite(buzzerPin, (15 - distance) * (255.0 / 15)); // Buzzer intensity based on distance
  } else {
    analogWrite(buzzerPin, 0); // Turn off buzzer if distance is safe
  }

  // Send IR signal only when the button is pressed
  if (digitalRead(buttonPin) == LOW) { 
    while (digitalRead(buttonPin) == LOW); // Wait for button release (debouncing)
    for (int i = 0; i < 5; i++) { 
      irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), 38); 
      delay(50); 
    }
  }
}