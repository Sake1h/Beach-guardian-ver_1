<img width="1599" height="899" alt="image" src="https://github.com/user-attachments/assets/66980464-ec4a-4b83-a08e-717633099e9d" />

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
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/f74d37f4-1f0a-40d6-8407-40493c7810dc" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/545bd368-1d3c-434a-a6e5-b7b2cfaac61d" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/86525e46-dbf0-4720-be3a-c6e96fb60ee4" />
<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/4555bcc3-6a77-4a72-9a14-a105331356da" />
<img width="1599" height="899" alt="image" src="https://github.com/user-attachments/assets/ed9c3fde-20b2-4d3f-8bc6-5870eaa93faa" />
<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/bb396ea2-f9e3-4705-9639-f8a94651e6bc" />
<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/6a00996d-a456-446e-8d10-bc355994d89b" />
<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/02d3e6f4-138b-49c5-9db1-da6b5a7008e6" />







