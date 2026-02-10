# 🚗 Arduino Automated Garage System

An intelligent Arduino-based garage automation system with RFID access control, ultrasonic proximity detection, IR remote control, and an integrated security alarm system.

## 📋 Overview

This project consists of two main components:
1. **Alarm System** (`alarm_system.ino`) - Advanced RFID-based gate control with security features
2. **Garage Controller** (`garage_controller.ino`) - Remote control and proximity detection for safe garage operation

## ✨ Features

### Alarm System
- **RFID Access Control**: Authorized card-based gate opening with up to 3 stored UIDs
- **Servo Motor Gate Control**: Automated gate opening/closing (0° to 90°)
- **IR Remote Alternative**: Backup IR remote control for gate operation
- **Intruder Detection**: Ultrasonic sensor-based unauthorized access detection
- **Visual/Audio Alarm**: RGB LED and audio alarm when potential intruder detected
- **Manual Override**: Physical button to silence alarm and reset system
- **Auto-Reset**: Smart reset functionality for continuous operation

### Garage Controller
- **Proximity Warning System**: Distance-based buzzer alerts (intensity increases as objects get closer)
- **IR Transmitter**: Button-triggered IR signal transmission to communicate with alarm system
- **Collision Prevention**: Alerts when objects are within 15cm
- **Manual Control**: Physical button for remote gate operation

## 🔧 Hardware Requirements

### Alarm System Components
- Arduino board (Mega recommended due to pin requirements)
- MFRC522 RFID reader module
- Servo motor (for gate mechanism)
- Ultrasonic sensor (HC-SR04 or similar)
- IR receiver module
- IR transmitter LED
- RGB LED (or separate LEDs on pins 3, 9, 10)
- Push buttons (pins 41, 43)
- RFID tags/cards (up to 3 authorized)

### Garage Controller Components
- Arduino board
- HC-SR04 Ultrasonic sensor
- IR transmitter LED
- Buzzer (PWM compatible)
- Push button

## 📌 Pin Configuration

### Alarm System
| Component | Pin |
|-----------|-----|
| RFID SS | 45 |
| RFID RST | 47 |
| Servo Motor | 11 |
| Ultrasonic Trig | 34 |
| Ultrasonic Echo | 33 |
| IR Receiver | 8 |
| LED Red/Green | 3, 9, 10 |
| Gate Sensor | 43 |
| Reset Button | 41 |
| Additional | 37, 39 |

### Garage Controller
| Component | Pin |
|-----------|-----|
| Ultrasonic Trig | 34 |
| Ultrasonic Echo | 35 |
| Buzzer | 10 |
| Button | 33 |
| IR Transmitter | 3 |


## 🎯 Usage

### Opening the Gate

**Method 1 - RFID Card:**
1. Approach the gate
2. Present authorized RFID card to reader
3. Gate opens automatically (servo moves to 90°)
4. Drive through
5. Press gate sensor button (pin 43) to close

**Method 2 - IR Remote:**
1. Stand within 15cm of sensor to trigger detection
2. Press button on garage controller
3. IR signal transmitted
4. Gate opens automatically
5. Press gate sensor button to close

### Security Features

- If an unauthorized RFID card is presented, the system checks distance
- If an object/person remains after unauthorized attempt, alarm sounds
- RGB LED cycles through colors while alarm is active
- Press the alarm reset button (pin 41) to silence and reset

## 📄 License

This project is open source and available under the MIT License.

## 👤 Author

**Andrew Chinomona**
- GitHub: [@Andrew-Chinomona](https://github.com/Andrew-Chinomona)

**Note**: This is a DIY project for educational purposes. Ensure proper safety measures when implementing automated gate systems.
