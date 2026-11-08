#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <esp_now.h>

//Esp #2's mac
uint8_t esp2Address[] = {
    0xEC, 0xE3, 0x34, 0x45, 0xAB, 0xE4};

//esp now channel
const int ESPNOW_CHANNEL = 1;

//Ultrasonic sensor pins

// FRONT
const int TRIG1 = 12;
const int ECHO1 = 14;

// LEFT
const int TRIG2 = 27;
const int ECHO2 = 26;

// RIGHT
const int TRIG3 = 25;
const int ECHO3 = 33;

typedef struct {
    int leftSpeed;
    int rightSpeed;
    int sieveActive;
} ControlMessage;

ControlMessage cmdData;

//sensor readings

float distance1 = 0;
float distance2 = 0;
float distance3 = 0;

//peer info for esp-now

esp_now_peer_info_t peerInfo;

//sieve state
bool sieveState = false;
//auto mode state
bool autoMode = false;

//server/ dashboard
const char* ap_ssid = "Beach Guardian";
const char* ap_pass = "beachguardian";

WebServer server(80);// dahsboard underneath
const char htmlPage[] = R"rawliteral(

<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Beach Guardian</title>
<style>
body {
    font-family: Arial;
    text-align: center;
}
button {
    width: 110px;
    height: 60px;
    margin: 5px;
    font-size: 18px;}
</style>
</head>
<body>
<h1>BEACH GUARDIAN</h1>
<button onclick="sendCommand('forward')">
Forward
</button>
<br>
<button onclick="sendCommand('left')">
Left
</button>
<button onclick="sendCommand('stop')">
STOP
</button>

<button onclick="sendCommand('right')">
Right
</button>

<br>
<button onclick="sendCommand('backward')">
Backward
</button>
<br><br>
<button onclick="sendCommand('sieve')">
Sieve
</button>
<br><br>
<button onclick="toggleAuto()">
AUTO / MANUAL
</button>
<h3>
Mode:
<span id="mode">MANUAL</span>
</h3>
<hr>
<p>
Front:
<span id="front">--</span>
cm
</p>
<p>
Left:
<span id="left">--</span>
cm
</p>
<p>
Right:
<span id="right">--</span>
cm
</p>
<script>
function sendCommand(command) {

    fetch('/cmd?command=' + command);      

}

function toggleAuto() {

    fetch('/auto')
    .then(response => response.text())
    .then(data => {
        document.getElementById("mode").innerText = data;
    });}
function updateSensors() {
    fetch('/sensors')
    .then(response => response.json())
    .then(data => {

        document.getElementById("front").innerText =
            data.front;

        document.getElementById("left").innerText =
            data.left;

        document.getElementById("right").innerText =
            data.right;
    });
}

setInterval(updateSensors, 500);
updateSensors();
</script>
</body>
</html>
)rawliteral";

//Sensor reading function
float readUltrasonic(
    int trigPin,
    int echoPin
) {
    digitalWrite(
        trigPin,
        LOW
    );
    delayMicroseconds(2);
    digitalWrite(
        trigPin,
        HIGH
    );
    delayMicroseconds(10);
    digitalWrite(
        trigPin,
        LOW
    );
    unsigned long duration =
        pulseIn(
            echoPin,
            HIGH,
            30000
        );

    if (duration == 0) {

        return -1.0;

    }

    return duration / 58.0;
}

void readSensors() {

    distance1 =
        readUltrasonic(
            TRIG1,
            ECHO1
        );

    delay(5);

    distance2 =
        readUltrasonic(
            TRIG2,
            ECHO2
        );

    delay(5);

    distance3 =
        readUltrasonic(
            TRIG3,
            ECHO3
        );
}

void sendEspNowCommand() {

    esp_err_t result =
        esp_now_send(
            esp2Address,
            (uint8_t*)&cmdData,
            sizeof(cmdData)
        );

    if (result == ESP_OK) {

        Serial.println(
            "ESP-NOW command sent"
        );

    }
    else {

        Serial.println(
            "ESP-NOW send failed"
        );
    }
}
void handleRoot() {

    server.send(
        200,
        "text/html",
        htmlPage
    );
}
//manual control commands
void handleCommand() {
    String command =
        server.arg("command");

    Serial.print(
        "Command: "
    );
    Serial.println(command);

    // Manual control disabled in AUTO
    if (autoMode) {

        server.send(
            200,
            "text/plain",
            "AUTO MODE ACTIVE"
        );
        return;
    }
    // FORWARD
    if (command == "forward") {

        cmdData.leftSpeed = 60;
        cmdData.rightSpeed = 60;
    }
    // BACKWARD
    else if (command == "backward") {
        cmdData.leftSpeed = -60;
        cmdData.rightSpeed = -60;
    }
    // LEFT
    else if (command == "left") {
        cmdData.leftSpeed = -50;
        cmdData.rightSpeed = 50;
    }

    // RIGHT
    else if (command == "right") {

        cmdData.leftSpeed = 50;
        cmdData.rightSpeed = -50;
    }

    // STOP
    else if (command == "stop") {

        cmdData.leftSpeed = 0;
        cmdData.rightSpeed = 0;
    }
    // SIEVE
    else if (command == "sieve") {

        sieveState = !sieveState;

        cmdData.sieveActive =
            sieveState ? 1 : 0;
    }
    else {
        server.send(
            400,
            "text/plain",
            "Unknown command"
        );

        return;
    }
    sendEspNowCommand();

    server.send(
        200,
        "text/plain",
        command
    );
}
void handleAutoMode() {

    autoMode = !autoMode;

    // Stop when switching modes
    cmdData.leftSpeed = 0;
    cmdData.rightSpeed = 0;

    sendEspNowCommand();

    if (autoMode) {

        Serial.println(
            "AUTO MODE ON"
        );

        server.send(
            200,
            "text/plain",
            "AUTO"
        );

    }
    else {

        Serial.println(
            "MANUAL MODE ON"
        );

        server.send(
            200,
            "text/plain",
            "MANUAL"
        );
    }
}

void handleSensors() {

    String json = "{";

    json += "\"front\":";
    json += String(
        distance1,
        1
    );

    json += ",\"left\":";
    json += String(
        distance2,
        1
    );

    json += ",\"right\":";
    json += String(
        distance3,
        1
    );

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}

void automaticObstacleAvoidance() {

    if (!autoMode) {

        return;
    }

    const float FRONT_LIMIT = 30.0;
    const float SIDE_LIMIT = 25.0;

    // Invalid front reading
    if (distance1 < 0) { return;
    }
    if (distance1 >= FRONT_LIMIT) {

        cmdData.leftSpeed = 60;
        cmdData.rightSpeed = 60;

        sendEspNowCommand();return;
    }

    //obstacle detected

    Serial.println(
        "Obstacle detected"
    );

    // Stop
    cmdData.leftSpeed = 0;
    cmdData.rightSpeed = 0;

    sendEspNowCommand();

    delay(200);
//if left is clearer than right and left is clear enough, turn left
    if (
        distance2 > SIDE_LIMIT &&
        distance2 >= distance3
    ) {

        Serial.println(
            "Turning LEFT"
        );

        cmdData.leftSpeed = -50;
        cmdData.rightSpeed = 50;
    }

    //if right is clearer than left and right is clear enough, turn right
    else if (
        distance3 > SIDE_LIMIT
    ) {

        Serial.println(
            "Turning RIGHT"
        );

        cmdData.leftSpeed = 50;
        cmdData.rightSpeed = -50;
    }
//if both r locked in

    else {

        Serial.println(
            "Both sides blocked"
        );

        cmdData.leftSpeed = -60;
        cmdData.rightSpeed = -60;
    }
    sendEspNowCommand();

    delay(500);

    // Resume forward
    if (autoMode) {

        cmdData.leftSpeed = 60;
        cmdData.rightSpeed = 60;

        sendEspNowCommand();
    }}
void setup() {

    Serial.begin(115200);

    delay(1000);

    // SENSOR PINS

    pinMode(
        TRIG1,
        OUTPUT
    );

    pinMode(
        ECHO1,
        INPUT
    );

    pinMode(
        TRIG2,
        OUTPUT
    );

    pinMode(
        ECHO2,
        INPUT
    );

    pinMode(
        TRIG3,
        OUTPUT
    );

    pinMode(
        ECHO3,
        INPUT
    );

    digitalWrite(
        TRIG1,
        LOW
    );

    digitalWrite(
        TRIG2,
        LOW
    );

    digitalWrite(
        TRIG3,
        LOW
    );
    cmdData.leftSpeed = 0;
    cmdData.rightSpeed = 0;
    cmdData.sieveActive = 0;

  //wifi func
    WiFi.mode(
        WIFI_AP_STA
    );

    WiFi.softAP(
        ap_ssid,
        ap_pass,
        ESPNOW_CHANNEL
    );

    IPAddress IP =
        WiFi.softAPIP();

    Serial.println();
    Serial.println(
        "----> readyy <----"
    );

    Serial.println(
        " BEACH GUARDIAN ESP32-A"
    );
    Serial.print(
        "WiFi: "
    );
    Serial.println(
        ap_ssid
    );
    Serial.print(
        "Dashboard: "
    );
    Serial.println(
        IP
    );
//esp now init
    if (
        esp_now_init()
        != ESP_OK
    ) { Serial.println(
            "ESP-NOW initialization FAILED"
        );

        return;
    }

    memset(
        &peerInfo,
        0,
        sizeof(peerInfo)
    );

    memcpy(
        peerInfo.peer_addr,
        esp2Address,
        6
    );
    peerInfo.channel =
        ESPNOW_CHANNEL;
    peerInfo.encrypt = false;

    if (
        esp_now_add_peer(
            &peerInfo
        )
        != ESP_OK
    ) {
        Serial.println(
            "Failed to add ESP32-B"
        );

        return;
    }
    server.on(
        "/",
        handleRoot
    );

    server.on(
        "/cmd",
        handleCommand
    );
    server.on(
        "/sensors",
        handleSensors
    );

    server.on(
        "/auto",
        handleAutoMode
    );

    server.begin();

    Serial.println(
        "HTTP server started"
    );

    Serial.println(
        "ESP32-A READY"
    );
}

//loop

void loop() {
    server.handleClient();

    readSensors();

    automaticObstacleAvoidance();

    delay(50);
}