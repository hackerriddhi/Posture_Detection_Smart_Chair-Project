# Smart Chair for Posture and Sitting-Time Monitoring 

This repository contains the firmware, circuit designs, and documentation for a low-cost, real-time posture detection system . The project uses an **Arduino Uno** and **Piezoelectric sensors** to monitor sitting habits and detect poor posture (slouching/leaning).

##  Concept
Modern lifestyles involve prolonged sitting with poor posture, which causes back pain and long-term health issues. This project provides a real-time solution to:
* **Detect Posture:** Identifies upright, slouching, and leaning positions.
* **Monitor Duration:** Tracks total sitting time to encourage breaks.
* **User Alerts:** Notifies users to correct their posture or move via visual and audio cues.

## Key Features
* **Real-time Monitoring:** Continuous tracking of pressure distribution across the seat and backrest.
* **Smart Alert Logic:** * **Timer-based:** Alerts the user after 45 minutes of continuous sitting.
  * **Haptic Feedback:** Triggers a Buzzer and LED when poor posture is detecte.
* **Verification Logic:** Implements a 3-second "hold time" to confirm posture changes before triggering alerts, preventing false alarms from natural shifting.
* **Auto-Reset:** The system automatically resets if the user leaves the chair for more than 30 seconds.

##  Hardware Configuration
The system is built on the **Arduino Uno** platform with the following pin assignments:

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **Seat Left Sensor** | A0 | Detects sitting presence and pressure |
| **Seat Center Sensor**| A1 | Primary posture and presence detection |
| **Seat Right Sensor** | A2 | Detects sitting presence and pressure |
| **Backrest Upper** | A3 | Detects upright vs. slouched posture |
| **Backrest Lower** | A4 | Detects upright vs. slouched posture |
| **Buzzer** | D9 | Audio alert |
| **LED** | D8 | Visual alert |



##  Logic Overview
The firmware follows a specific logic to ensure accuracy:
1. **Thresholding:** If the sensor value falls below **900**, pressure is detected.
2. **Timing:** A posture must be held for **3000ms (3 seconds)** before an alert is triggered.
3. **Alert Duration:** Once triggered, the LED and Buzzer remain active for **5 seconds** to prompt correction.

##  Tech Stack
* **Language:** C++ (Arduino Framework)
* **IDE:** VS Code + PlatformIO / Arduino IDE
* **Version Control:** Git/GitHub

