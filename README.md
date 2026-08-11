<img width="1183" height="480" alt="image" src="https://github.com/user-attachments/assets/db738ac9-93eb-4ec8-9902-16d3e9e3a2f4" />
#Beach-Cleaning Rover (The Beest Challenge)
An open-source, dual-mode autonomous and remote-controlled rover designed to patrol beaches, scoop up surface-level sand and debris, and separate plastics using an active vibrating sieve system.

## Project Overview
Marine plastic pollution is a massive global crisis, and a big chunk of it ends up as microplastics and debris trapped in the sand in beaches. This project aims to build an efficient, lightweight, and capable robotic solution that can comb beaches, sift through sand, and collect surface plastics without disrupting the local environment.

##Key Features
**Dual-Mode Control**: Switch seamlessly between Manual Mode (via a local Wi-Fi web dashboard hosted on the ESP32) and Autonomous Mode.
**Active Sieve Mechanism:** A front-mounted scoop and vibrating mesh screen designed to trap plastic debris while allowing clean sand to fall back through.
* **All-Terrain Skid-Steer:** Powered by high-torque 12V metal-gear motors and wide wheels/tracks to handle the resistance of sand.
**Weather-Resistant Build:** Sealed electronics compartment to protect internal microcontrollers from fine dust and moisture.

##Bill of Materials 
**ESP32 Devkit Board** x2 Main microcontroller, Wi-Fi web server, and logic handler 
**L298N Motor Driver** x1 Controls speed and direction of drive motors 
**12V High-Torque DC motors** x2 Skid-steer drivetrain propulsion 
**Wide Rubber Wheels** x4 Maximizes traction on loose sand 
**HC-SR04 Ultrasonic** x2 Obstacle detection for autonomous navigation 
**Sieve servo** x2 Lifts the sieve mechanism
**12V LI-PO** x1 High-current power source for motors and electronics 
**DC-DC Buck Converter** x2 Steps down battery voltage to 5V for the ESP32 and servos
**Stainless Steel Wire Mesh** x1 Sifting screen for plastic separation 
**Waterproof Enclosure Box** x1 Protects electronics from sand and dust 3D printed
**Aluminum frame** x1 For structural integrity 
**100 micro F capacitors** x3 For the microcontrollers
**1.1K ohm resistors** x9 For voltage dividers
**Perfboards** x1 For components to be soldered on
**Raspberry Pi Zero W** x1 Color recognition for detecting plastics
**Generic Webcam** x1 to enable vision
**WIRES/SWITCHES/SOLDER TIN**
