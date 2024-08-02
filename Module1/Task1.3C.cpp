const int pirPin = 2;  // Pin connected to the PIR sensor's output
const int ultrasonicPin = 3; // Pin connected to the Ultrasonic sensor's SIG pin
const int ledPin = 13; // Pin connected to the LED

volatile bool motionDetected = false; // Flag for motion detection
const int distanceThreshold = 30; // Distance threshold in cm

void setup() {
  pinMode(pirPin, INPUT);  // Set PIR sensor pin as input
  pinMode(ultrasonicPin, INPUT); // Set Ultrasonic sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Initialize serial communication

  // Attach interrupt to the PIR sensor pin, triggering on CHANGE
  attachInterrupt(digitalPinToInterrupt(pirPin), motionISR, CHANGE);
}

void loop() {
  // Measure distance using the Ultrasonic sensor
  long duration, distance;
  
  // Send a short pulse to trigger the Ultrasonic sensor
  pinMode(ultrasonicPin, OUTPUT);
  digitalWrite(ultrasonicPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicPin, LOW);
  
  pinMode(ultrasonicPin, INPUT);
  duration = pulseIn(ultrasonicPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Check both conditions: motion detected and distance below threshold
  if (motionDetected && distance < distanceThreshold) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED if both conditions are met
    Serial.println("Motion detected and object within threshold distance, LED Turned On");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED if either condition is not met
    Serial.println("Conditions not met, LED Turned Off");
  }

  delay(100);  // Delay for a short period to avoid flooding the Serial Monitor
}

// Interrupt Service Routine (ISR) for motion detection
void motionISR() {
  motionDetected = digitalRead(pirPin); // Update motionDetected based on the PIR sensor output
}