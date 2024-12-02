#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include "arduino_secrets.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "172.20.116.111";
int        port     = 1883;
const char topic[]  = "paho/test/topic";

const int ROWS = 8;
const int COLUMNS = 12;
byte matrixNextFrame[ROWS][COLUMNS];

void printMacAddress(byte mac[]) {
  for (int i = 0; i < 6; i++) {
    if (i > 0) {
      Serial.print(":");
    }
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
  }
  Serial.println();
}

void setup() {
  matrix.begin();
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.println("Attempting to connect to SSID: ");
  Serial.println(ssid);

  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);


  while (WiFi.begin(ssid) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep alive which avoids being disconnected by the broker
  mqttClient.poll();
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");

  // Serial.println(" bytes:");

  String msg = "";
  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    msg += (char)mqttClient.read();
  }
  Serial.println(msg);
  Serial.println();

  int index = 0; // Index for the string
  for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
          if (index < msg.length()) {
              matrixNextFrame[i][j] = msg[index] - '0'; // Convert char to int
              index++;
          } else {
              matrixNextFrame[i][j] = 0; // Default value if string is too short
          }
      }
  }

  Serial.print(msg);
  updateLEDArray(matrixNextFrame);
  
  //return msg;
}

void updateLEDArray(byte nextFrame[ROWS][COLUMNS]) {
  matrix.renderBitmap(nextFrame, 8, 12);
}