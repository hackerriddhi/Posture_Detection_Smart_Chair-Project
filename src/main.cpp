#include <Arduino.h>

// --- Pin Assignments ---
#define PIEZO_CENTER A1     // Center piezo sensor
#define BUZZER_PIN 9        // Buzzer pin (follows LED)
#define LED_PIN 8           // LED pin

#define THRESHOLD 900       // Sensor reads < 900 when pressed
#define HOLD_TIME 3000      // Must hold for 3 seconds
#define ALERT_DURATION 5000 // Keep LED/Buzzer ON for 5 seconds

// --- Variables ---
unsigned long pressStartTime = 0;
unsigned long alertStartTime = 0;
bool isPressed = false;
bool alertActive = false;
bool sensorReleased = true;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);  // Buzzer OFF initially
  digitalWrite(LED_PIN, LOW);     // LED OFF initially

  Serial.begin(9600);
  delay(2000);  // Optional warm-up
}

void loop() {
  int sensorValue = analogRead(PIEZO_CENTER);
  Serial.println(sensorValue);

  unsigned long currentTime = millis();

  // --- If alert is ON, keep LED & buzzer ON for 5 seconds ---
  if (alertActive) {
    if (currentTime - alertStartTime >= ALERT_DURATION) {
      digitalWrite(LED_PIN, LOW);      // LED OFF
      digitalWrite(BUZZER_PIN, LOW);   // Buzzer OFF (follows LED)
      alertActive = false;
      sensorReleased = false;
      Serial.println("🔕 LED/Buzzer OFF after 5 sec");
    }
    return;
  }

  // --- Wait until sensor is released before next trigger ---
  if (!sensorReleased && sensorValue > THRESHOLD) {
    sensorReleased = true;
    Serial.println("🟢 Sensor released — Ready for next alert");
  }

  // --- Detect valid press & trigger LED (and buzzer with it) ---
  if (sensorValue < THRESHOLD && sensorReleased) {
    if (!isPressed) {
      pressStartTime = currentTime;
      isPressed = true;
    }

    if (currentTime - pressStartTime >= HOLD_TIME) {
      digitalWrite(LED_PIN, HIGH);     // LED ON
      digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON (follows LED)
      alertStartTime = currentTime;
      alertActive = true;
      isPressed = false;
      Serial.println("✅ Held 3 sec — LED/Buzzer ON for 5 sec");
    }
  } else {
    isPressed = false;
    pressStartTime = 0;
  }

  delay(100);
}