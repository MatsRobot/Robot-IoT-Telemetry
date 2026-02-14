# PondGuard: IoT Water Level & Temperature Monitor

A smart monitoring solution designed to prevent pond drainage disasters and track winter thermal stratification.

<p align="center">
<img width="600" height="771" alt="PondGuard1" src="https://github.com/user-attachments/assets/5a6b6f9a-1895-4b2e-9d01-fa154d5c94f0" />
</p>
---

## 🚀 The Backstory

This project was born out of a near-catastrophe. A damaged pump return tube began draining my pond without any warning. I fortunately caught it just in time, but it highlighted a critical need: **real-time visibility into pond health.**

PondGuard provides a 24/7 safety net, ensuring that if water levels drop or temperatures reach critical lows, I know about it before it's too late.

## ✨ Key Features

* **Laser-Precision Level Sensing:** Uses a VL53L0X laser distance sensor to measure the height of a floating ball within a stabilized tube.
* **Thermal Profiling:** Monitors water temperature at multiple depths—crucial for fish survival during freezing winter months.
* **Cloud Integration:** Streams live data to **ThingSpeak** for historical logging and visualization.
* **Mobile Alerts:** Sends an instant alarm to my phone if the water level drops below a set value.
* **On-Device Display:** Real-time local readings via the integrated Heltec OLED screen.

## 🛠️ Hardware Stack

* **Microcontroller: Heltec WiFi Kit 8 (ESP8266 based)**
    * Integrated 0.91-inch 128x32 OLED display.
    * Built-in Wi-Fi for cloud connectivity.
* **Sensors:**
    * **Level:** Time-of-Flight (ToF) Laser Distance Sensor.
    * **Temperature:** DS18B20 Waterproof probes (Multiple sensors on a 1-wire bus).
* **Enclosure:** Custom-built probe housing with a transparent waterproof top.

<p align="center">
<img width="500" height="361" alt="PondGuard3" src="https://github.com/user-attachments/assets/171bd956-7fdd-4593-bfbd-5b4602a0c185" />
</p>

<p align="center">
<img width="500" height="361" alt="PondGuard3" src="https://github.com/user-attachments/assets/025bb8ce-f848-456f-ae75-a976fe6db381" />
</p>


## 📐 How It Works

### The Level Sensor
To avoid the inaccuracies of ultrasonic sensors or the corrosion of resistive probes, this project uses a **floating ball mechanism**. A laser sensor mounted at the top of a PVC tube measures the distance to a ball floating on the water surface. As the pond level drops, the distance increases, triggering an alarm if it exceeds the "Safe" limit.

### Winter Temperature Monitoring
In winter, pond water stratifies (warmer water sinks to the bottom). By placing sensors at different levels, the system monitors if the "warm zone" is maintained, helping to decide if de-icers or aerators need adjustment.

### Data Flow
1.  **ESP8266** wakes up and polls the sensors.
2.  Data is displayed locally on the **Heltec OLED**.
3.  Data is transmitted via **Wi-Fi** to the **ThingSpeak API**.
4.  ThingSpeak or a connected mobile app triggers a notification if levels are critical.

<p align="center">
  <img width="692" src="https://github.com/user-attachments/assets/4115fb1c-bfbe-4537-bb70-f183b4527ff1" alt="Installation Setup" />
</p>

## 📜 License

This project is open-source. Feel free to use, modify, and improve it for your own pond!


