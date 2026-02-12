# Smart Garden Irrigation System (ESP8266)

An IoT-based smart garden monitoring and irrigation system built using ESP8266 and the Blynk IoT Platform.  
This project monitors environmental conditions and automates plant watering while allowing real-time control and monitoring via web and mobile dashboards.

---

## Project Overview

The Smart Garden Irrigation System is designed to help maintain optimal plant conditions by monitoring soil moisture, temperature, humidity, water tank level, and detecting motion near the garden area.  
It also supports manual pump control through Blynk, making it suitable for small farms, home gardens, and academic IoT projects.

---

## Features

- Soil moisture monitoring  
- Temperature and humidity monitoring (DHT11)  
- Water level monitoring  
- Motion / intruder detection (PIR sensor)  
- Water pump control using relay  
- Real-time monitoring via Blynk Web and Mobile  
- WiFi-enabled system using ESP8266  

---

## System Logic

- Reads soil moisture and water level using a shared analog pin (A0)  
- Displays sensor data on the Blynk dashboard  
- Allows manual ON/OFF control of the water pump  
- Monitors water tank level to avoid dry pump operation  
- Detects motion and sends status to the dashboard  

---

## Hardware Components

- ESP8266 (NodeMCU)  
- Soil Moisture Sensor  
- DHT11 Temperature and Humidity Sensor  
- PIR Motion Sensor  
- Water Level Sensor  
- Relay Module  
- Water Pump  
- Motor Driver (L298N or equivalent)  
- Jumper wires
- Recycled power plug 

---

## Software and Technologies

- Arduino C++ (Embedded Systems)  
- ESP8266WiFi Library  
- Blynk IoT Platform  
- DHT Sensor Library  
- Arduino IDE  

---

## Pin Configuration

| Component           | ESP8266 Pin |
|--------------------|------------|
| Soil Moisture      | A0         |
| Water Level Sensor | A0         |
| DHT11              | D5         |
| PIR Sensor         | D6         |
| Soil Button        | D3         |
| Water Button       | D4         |
| Motor Enable (ENB) | D7         |
| Motor IN3          | D1         |
| Motor IN4          | D2         |

---

## Blynk Virtual Pins

| Virtual Pin | Function                  |
|------------|---------------------------|
| V0         | Soil Moisture Display     |
| V1         | Pump ON/OFF Control       |
| V2         | Water Level Display       |
| V3         | Temperature               |
| V4         | Humidity                  |
| V5         | Motion Detection          |

---

## How to Run the Project

1. Install Arduino IDE  
2. Add ESP8266 board support  
3. Install required libraries:
   - Blynk
   - DHT Sensor Library  
4. Configure the following in the code:
   - Blynk Template ID  
   - Auth Token  
   - WiFi SSID and Password  
5. Upload the code to ESP8266  
6. Open the Blynk Web or Mobile Dashboard  

---

## Applications
 
- Enhanced automation of mini farms or garden 
- Academic and capstone IoT projects

---

## License

This project is intended for educational purposes.  
You are free to use and modify it with proper credit.
