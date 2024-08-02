const int pirPin = 2;  // Pin connected to the PIR sensor's output
const int ledPin = 13; // Pin connected to the LED

volatile bool motionDetected = false; // Flag for motion detection

void setup() {
  pinMode(pirPin, INPUT);  // Set PIR sensor pin as input
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Initialize serial communication

  // Attach interrupt to the PIR sensor pin, triggering on CHANGE
  attachInterrupt(digitalPinToInterrupt(pirPin), motionISR, CHANGE);
}

void loop() {
  if (motionDetected) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED if motion is detected
    Serial.println("Motion detected, LED Turned On");
  } else {
    digitalWrite(ledPin, LOW);   // Turn off the LED if no motion is detected
    Serial.println("No motion, LED Turned Off");
  }
  delay(100);  // Delay for a short period to avoid flooding the Serial Monitor
}

// Interrupt Service Routine (ISR) for motion detection
void motionISR() {
  motionDetected = digitalRead(pirPin); // Update motionDetected based on the PIR sensor output
}