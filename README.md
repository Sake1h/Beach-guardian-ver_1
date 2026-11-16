<img width="899" height="1599" alt="image" src="https://github.com/user-attachments/assets/31995006-d7a5-4973-bfb2-3955853cf3af" />

# Beach Guardian

A remotely controlled beach-cleaning rover designed to collect plastic debris from sand while allowing sand to fall back through a mesh sieve.

## Project Overview

Beach Guardian is a robotic prototype designed to help collect plastic waste from sandy environments.

The robot uses a front-mounted scoop with a mesh underside. The scoop can be lowered to collect a mixture of sand and debris. The scoop can then be raised using two servos, allowing sand to fall through the mesh while larger pieces of plastic remain in the scoop.

The robot is controlled through a local Wi-Fi web dashboard and uses two ESP32 microcontrollers.

## Estimated Project Cost

The following is an approximate estimate of the hardware cost for **Beach Guardian V1**. Prices may vary depending on the supplier, brand, and purchase quantity.

| Component                       | Quantity | Estimated Unit Cost | Estimated Total |
| ------------------------------- | -------: | ------------------: | --------------: |
| ESP32 Development Board         |        2 |              $13.00 |          $26.00 |
| HC-SR04 Ultrasonic Sensor       |        3 |               $2.00 |           $6.00 |
| L298N Motor Driver              |        1 |               $3.00 |           $3.00 |
| DC Geared Motor                 |        2 |              $10.00 |          $20.00 |
| Robot Chassis                   |        1 |              $15.00 |          $15.00 |
| Wheels                          |        2 |               $4.00 |           $8.00 |
| Servo Motor                     |        2 |               $4.00 |           $8.00 |
| Buck Converter                  |        2 |               $3.00 |           $6.00 |
| Battery                         |        1 |              $25.00 |          $25.00 |
| 1000 µF Capacitors              |        3 |               $1.00 |           $3.00 |
| 1.1 kΩ Resistors                |        6 |               $0.10 |           $0.60 |
| Fuse + Holder                   |        1 |               $3.00 |           $3.00 |
| Power Switch                    |        1 |               $2.00 |           $2.00 |
| Hook-up / Jumper Wire           | Assorted |               $5.00 |           $5.00 |
| Perfboard                       |        1 |               $3.00 |           $3.00 |
| Solder & Miscellaneous Hardware | Assorted |               $8.00 |           $8.00 |
| **Estimated Total**             |          |                     |   **~$140 USD** |

 Cost Notes

* The two ESP32 boards were purchased for **5 OMR each**, approximately **$13 USD each**.
* The estimate represents the approximate replacement cost of the hardware used in the project.
* A large reason for the increased prices are due to current geopolitical situations which make shipping charges expensive.
* **Raspberry Pi, webcam, and USB hub are not included**, as the planned plastic/colour recognition system was removed from Beach Guardian V1.
* Development equipment such as a personal computer is not included in the project cost.


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

 ESP32 #1
- Hosts the Wi-Fi dashboard
- Reads the 3 ultrasonic sensors
- Displays sensor readings
- Receives driving commands from the dashboard
- Sends commands to ESP32 #2 using ESP-NOW


### ESP32 #1 — Sensor & Dashboard
Responsible for:
- Ultrasonic sensors
- Sensor data
- Web dashboard
- Sending motor commands


### ESP32 #2 — Motor Control
Responsible for:
- Receiving commands
- PWM motor control
- L298N control
- Left/right motor operations






