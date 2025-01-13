
// This ESP32 code sends simulated voltage data to an MQTT server. You can modify it to suit your needs.

#include <WiFi.h>
#include <ArduinoMqttClient.h>

// Wi-Fi network configuration
#define SECRET_SSID "SSID"         // Your Wi-Fi SSID
#define SECRET_PASS "password"     // Your Wi-Fi password

// MQTT Broker
const char* broker = "192.168.1.100";   // MQTT broker IP address
int port = 1883;                           // MQTT broker port
const char* topic = "Sensor_data";      // Topic where data will be published
    
// Message send interval in milliseconds
const long interval = 5000;
unsigned long previousMillis = 0;

// MQTT client
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Function to connect the ESP32 to Wi-Fi
void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  connectWiFi();
  
  // Set up MQTT broker connection
  mqttClient.setId("ESP32Client");
  mqttClient.setUsernamePassword("", ""); // If your MQTT broker doesn't require credentials, leave empty.
  
  // Attempt connection to MQTT broker
  while (!mqttClient.connect(broker, port)) {
    Serial.println("Error connecting to MQTT broker. Retrying...");
    delay(1000);
  }
  Serial.println("Connected to MQTT broker");
}

void loop() {
  // Keep the connection to the MQTT broker alive
  mqttClient.poll();

  unsigned long currentMillis = millis();
  
  // Send data at the specified interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    float simulatedVoltage = random(1200, 2401) / 100.0;

    // Send the simulated voltage to the MQTT broker
    Serial.print("Sending simulated voltage: ");
    Serial.println(simulatedVoltage);

    mqttClient.beginMessage(topic);
    mqttClient.print(simulatedVoltage);
    mqttClient.endMessage();
    
    Serial.println("Data sent");
  }

  // Reconnect to the broker if the connection is lost
  if (!mqttClient.connected()) {
    Serial.println("Disconnected from MQTT broker. Attempting to reconnect...");
    while (!mqttClient.connect(broker, port)) {
      Serial.println("Retrying connection...");
      delay(1000);
    }
    Serial.println("Reconnected to MQTT broker.");
  }
}

