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
**ESP32 NodeMCU Board** x1 Main microcontroller, Wi-Fi web server, and logic handler 
**Dual Channel Motor Driver** x1 Controls speed and direction of drive motors 
**12V High-Torque Gearmotors** x2 Skid-steer drivetrain propulsion 
**Wide Rubber Wheels / Tracks** x4 Maximizes traction on loose sand 
**Omni-Wheel / Caster** x1 Rear/front balance and stability 
**JSN-SR04T Waterproof Ultrasonic** x2 Obstacle detection for autonomous navigation 
**Vibration Motor / Servo** x1 Shakes the collection mesh sieve 
**2S / 3S LiPo Battery** x1 High-current power source for motors and electronics 
**DC-DC Buck Converter** x1 Steps down battery voltage to 5V for the ESP32 
**Stainless Steel Wire Mesh** x1 Sifting screen for plastic separation 
**Waterproof Enclosure Box** x1 Protects electronics from sand and dust 
