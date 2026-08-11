#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <ESP32Servo.h>
//l298N pins

// Left motor
#define ENA 18
#define IN1 32
#define IN2 4

// Right motor
#define ENB 19
#define IN3 27
#define IN4 5
//servo pins

#define SERVO1_PIN 13
#define SERVO2_PIN 23

//servo positions
#define SERVO1_DOWN 90
#define SERVO1_UP   135
#define SERVO2_DOWN 90
#define SERVO2_UP   45
Servo sieveServo1;
Servo sieveServo2;
//pwm settings
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
//espnow
typedef struct {
    int leftSpeed;
    int rightSpeed;
    int sieveActive;
} ControlMessage;
ControlMessage receivedCommand;

//motor control function

void setMotor(
    int speed,
    int in1,
    int in2,
    int pwmChannel
) {
    speed = constrain(speed, -255, 255);
    if (speed > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        ledcWrite(
            pwmChannel,
            speed
        );
    }
    else if (speed < 0) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        ledcWrite(
            pwmChannel,
            -speed
        );
    }

    else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        ledcWrite(
            pwmChannel,
            0
        );}}
//both motors control function
void setMotorSpeeds(
    int leftSpeed,
    int rightSpeed
) {
    setMotor(
        leftSpeed,
        IN1,
        IN2,
        PWM_CHANNEL_A
    );

    setMotor(
        rightSpeed,
        IN3,
        IN4,
        PWM_CHANNEL_B
    );
}
//stop both motors

void stopMotors() {
    setMotorSpeeds(0, 0);
}

void onDataReceive(
    const uint8_t *mac,
    const uint8_t *incomingData,
    int len
) {
    if (len != sizeof(ControlMessage)) {

        Serial.print("Invalid packet size: ");
        Serial.println(len);

        return;}
    // Copy received command
    memcpy(
        &receivedCommand,
        incomingData,
        sizeof(receivedCommand)
    );
//motor commands
    setMotorSpeeds(
        receivedCommand.leftSpeed,
        receivedCommand.rightSpeed
    );
//sieve control
    if (receivedCommand.sieveActive) {

        // Lift / tilt scoop
        sieveServo1.write(SERVO1_UP);
        sieveServo2.write(SERVO2_UP);

    } else {
        // Lower scoop
        sieveServo1.write(SERVO1_DOWN);
        sieveServo2.write(SERVO2_DOWN);
    }

    Serial.print("Left: ");
    Serial.print(receivedCommand.leftSpeed);

    Serial.print(" | Right: ");
    Serial.print(receivedCommand.rightSpeed);

    Serial.print(" | Sieve: ");
    Serial.println(receivedCommand.sieveActive);
}

//setup function
void setup() {

    Serial.begin(115200);

    delay(1000);
//motrs pins setup
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
//pwm
    ledcSetup(
        PWM_CHANNEL_A,
        PWM_FREQ,
        PWM_RESOLUTION
    );
    ledcSetup(
        PWM_CHANNEL_B,
        PWM_FREQ,
        PWM_RESOLUTION
    );
    ledcAttachPin(
        ENA,
        PWM_CHANNEL_A
    );
    ledcAttachPin(
        ENB,
        PWM_CHANNEL_B
    );
    stopMotors();
//servo setup
    sieveServo1.setPeriodHertz(50);
    sieveServo2.setPeriodHertz(50);

    sieveServo1.attach(
        SERVO1_PIN,
        500,
        2400
    );
    sieveServo2.attach(
        SERVO2_PIN,
        500,
        2400
    );
    // Start with scoop lowered
    sieveServo1.write(SERVO1_DOWN);
    sieveServo2.write(SERVO2_DOWN);
//wifi
    WiFi.mode(WIFI_STA);

    // ESP1 uses ESP-NOW channel 1
    esp_wifi_set_channel(
        1,
        WIFI_SECOND_CHAN_NONE
    );

    Serial.println();
    Serial.println(" BEACH GUARDIAN ESP32-B");
    Serial.print("ESP32-B MAC: ");
    Serial.println(WiFi.macAddress());

    //init esp now
    if (esp_now_init() != ESP_OK) {

        Serial.println(
            "ESP-NOW initialization FAILED"
        );

        return;
    }

    esp_now_register_recv_cb(
        onDataReceive
    );

    Serial.println(
        "ESP-NOW receiver ready."
    );

    Serial.println(
        "Waiting for commands..."
    );
}//final loop
void loop() {
    delay(10);
}