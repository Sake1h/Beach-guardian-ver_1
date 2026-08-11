<img width="1183" height="480" alt="image" src="https://github.com/user-attachments/assets/db738ac9-93eb-4ec8-9902-16d3e9e3a2f4" />
# Beach Guardian

A remotely controlled beach-cleaning rover designed to collect plastic debris from sand while allowing sand to fall back through a mesh sieve.

## Project Overview

Beach Guardian is a robotic prototype designed to help collect plastic waste from sandy environments.

The robot uses a front-mounted scoop with a mesh underside. The scoop can be lowered to collect a mixture of sand and debris. The scoop can then be raised using two servos, allowing sand to fall through the mesh while larger pieces of plastic remain in the scoop.

The robot is controlled through a local Wi-Fi web dashboard and uses two ESP32 microcontrollers.

## What the Final Prototype Does

- Remote driving through a web dashboard
- Forward, backward, left and right movement
- Motor speed control using PWM
- Three ultrasonic distance sensors
- Live sensor readings displayed on the dashboard
- Two-servo scoop/sieve mechanism
- ESP-NOW communication between the two ESP32s
- 12 V battery-powered drivetrain
- 5 V regulated electronics and servo power
                    12 V Battery
                         |
                    Main Switch
                         |
              +----------+----------+
              |                     |
           L298N                 LM2596
              |                     |
         DC Motors                 5 V
                                    |
                         +----------+----------+
                         |                     |
                       ESP32 #1             Servos
                         |
             +-----------+-----------+
             |                       |
       Ultrasonic Sensors        Wi-Fi
             |                       |
             +--> Dashboard <--------+
                         |
                      ESP-NOW
                         |
                      ESP32 #2
                         |
                  +------+------+
                  |             |
                L298N        Servos
                  |
              DC Motors
  
 ESP32 #1
- Hosts the Wi-Fi dashboard
- Reads the 3 ultrasonic sensors
- Displays sensor readings
- Receives driving commands from the dashboard
- Sends commands to ESP32 #2 using ESP-NOW


## Firmware

The ESP32 #1 firmware is contained in this repository.

Main source:
src/main.cpp

Supporting modules:
src/dashboard.cpp
src/dashboard.h
src/motors.cpp
src/motors.h


diagram for initial power supply
┌──────────────┐
│  12V BATTERY │
└──────┬───────┘
       │
    ┌──▼───┐
    │SWITCH│
    └──┬───┘
       │
   ┌───┴───────────────┐
   │                   │
┌──▼────────┐    ┌─────▼──────┐
│  BUCK #1  │    │   BUCK #2  │
│ 12V → 5V  │    │  12V → 5V  │
└────┬──────┘    └─────┬──────┘
     │                 │
  ESP32 #1          ESP32 #2


  ## Software

### ESP32 #1 — Sensor & Dashboard
Responsible for:
- Ultrasonic sensors
- Sensor data
- Web dashboard
- Sending motor commands

[View ESP32 #1 Code](ESP32_1_Sensors/)

### ESP32 #2 — Motor Control
Responsible for:
- Receiving commands
- PWM motor control
- L298N control
- Left/right motor operation

[View ESP32 #2 Code](ESP32_2_Motor_Control/)
