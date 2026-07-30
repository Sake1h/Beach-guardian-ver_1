#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ap_said = "Beach Guardian";
const char* ap_pass = "beachguardian";
WebServer server(80);

const char htmlPage[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Beach Guardian control dashboard</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    body{ font-family: Arial, Helvetica, sans-serif; text-align: center; margin: 0px auto;background-color: #f1f1f1;}
    h1{color: #0044d8;}
    .btn{background-color: #9dcdf5; border: none; color: white; padding: 20px; text-decoration: none; font-size: 18px; margin: 2px; cursor: pointer;}
    .btn:active {background: #5185f5;}
    .row{display: flex; flex-wrap: wrap; justify-content: center;}
    </style>
</head>
<body>
    <h1>Beach Guardian Control Dashboard</h1>
    <div class="row"><button class="btn" onclick="send('forward')">Forward</button></div>
    <div class="row">
        <button class="btn" onclick="send('left')">Left</button>
        <button class="btn" onclick="send('stop')">Stop</button>
        <button class="btn" onclick="send('right')">Right</button>
    </div>
    <div class="row"><button class="btn" onclick="send('backward')">Backward</button></div>
    <div class="row"><button class="btn" onclick="send('sieve')">Sieve</button></div>
    <p id="status">Ready</p>

    <script>
        function send(command) {
            fetch('/cmd?command=' + command)
                .then(response => response.text())
                .then(data => {
                    document.getElementById('status').innerText = 'Last: ' + data;
                })
                                  .catch(error => console.error('Error:', error));
        }
                    </script>
</body> 
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleCommand() {
    String command = server.arg("command");
    Serial.println("Received command: " + command);

    // the motor stuff (placeholder)

    if (command == "forward") {
       
    } else if (command == "backward") {
        
    } else if (command == "left") {
        
    } else if (command == "right") {
        
    } else if (command == "stop") {
        
    } else if (command == "sieve") {
        
    }

    server.send(200, "text/plain", command);
}
  void setup() {
    Serial.begin(115200);
    delay(1000); // Give time for Serial to initialize

    WiFi.softAP(ap_said, ap_pass);
    IPAddress IP = WiFi.softAPIP();

    Serial.println("Access Point Started");
    Serial.print("Connect to WiFi and open IP Address: ");
    Serial.println(IP);

    server.on("/", handleRoot);
    server.on("/cmd", handleCommand);
    server.begin();
Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}