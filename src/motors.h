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