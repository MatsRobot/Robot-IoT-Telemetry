# 🤖 Robot IoT Telemetry & Cloud Integration (ThingSpeak)

A versatile IoT framework for capturing, transmitting, and visualizing real-time robot sensor data. This system bridges the gap between physical hardware and cloud-based analytics using the **ThingSpeak** API.



<p align="center">
<img width="600" alt="Robot IoT Overview" src="https://github.com/user-attachments/assets/5a6b6f9a-1895-4b2e-9d01-fa154d5c94f0" />
</p>

---

## 🚀 The Mission
Modern robotics requires more than just local control; it requires **telemetry**. This project provides a robust template for connecting robot sensors (distance, temperature, orientation) to the cloud. 

While originally developed for environmental monitoring (the **PondGuard** case study), this architecture is now the backbone for my mobile robotics projects, allowing for 24/7 remote health monitoring and data logging.

## ✨ Framework Features

* **Cloud-Native Architecture:** Seamless integration with **ThingSpeak** for live graphing and data persistence.
* **Precision Distance Sensing:** Implementation of Time-of-Flight (ToF) Laser sensors for high-accuracy obstacle or level detection.
* **Multi-Node Thermal Monitoring:** Supports 1-Wire protocol for multiple temperature sensors, ideal for monitoring motor heat or battery pack health.
* **Edge Visualization:** Real-time data output on local OLED displays for debugging without a PC.
* **Remote Alarming:** Automated triggers that send mobile notifications if robot parameters (like battery voltage or distance) hit critical thresholds.

## 🛠️ Hardware Stack

* **Microcontroller:** Heltec WiFi Kit 8 (ESP8266)
    * Integrated 0.91-inch OLED.
    * Low-power WiFi for long-range robot-to-cloud communication.
* **Sensors:** * **Distance:** VL53L0X Laser ToF Sensor.
    * **Temp:** DS18B20 Waterproof probes.
* **Connectivity:** ThingSpeak IoT REST API.

## 📈 Proven Implementation: "PondGuard"
The first successful deployment of this framework was **PondGuard**, a mission-critical system designed to prevent pond drainage and monitor winter thermal stratification.

<p align="center">
<img width="400" alt="Sensor Module" src="https://github.com/user-attachments/assets/171bd956-7fdd-4593-bfbd-5b4602a0c185" />
<img width="400" alt="Telemetry View" src="https://github.com/user-attachments/assets/025bb8ce-f848-456f-ae75-a976fe6db381" />
</p>

### How it Works:
1.  **Sensing:** The hub polls the Laser sensor (measuring a float-ball for level) and the DS18B20 probes.
2.  **Processing:** The ESP8266 calculates deltas and formats the JSON/HTTP payload.
3.  **Cloud Sync:** Data is pushed to the cloud via WiFi.
4.  **Action:** If the distance exceeds a "Safe" limit (indicating a leak or low level), an alarm is triggered via ThingSpeak React or IFTTT.

<p align="center">
  <img width="692" src="https://github.com/user-attachments/assets/4115fb1c-bfbe-4537-bb70-f183b4527ff1" alt="Installation Setup" />
</p>

## 🔧 Future Robotics Applications
This IoT stack is currently being adapted for:
* **Battery Management Systems (BMS):** Monitoring cell temperatures and voltage via ThingSpeak.
* **Autonomous Navigation:** Logging ultrasonic and laser distance data to map environmental density and path efficiency.

## 📜 License
This project is open-source. Feel free to use and adapt this IoT telemetry framework for your own robotic or environmental projects!

```
