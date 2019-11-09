/**
 * Name: Hello_AwsIoT.ino
 *
 * M5StackでAWS IoTにつなぎ、Publish/Subscribeを行うサンプル
 */
#include <M5Stack.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

// WiFi Setting
const char* ssid = "";
const char* password = "";

// AWS IoT Setting
const char* awsEndpoint = "xxx.xxx.xxx.amazonaws.com";
const int awsPort = 8883;
const char* pubTopic = "pub01";
const char* subTopic = "sub01";

const char* rootCA =
    "-----BEGIN CERTIFICATE-----\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "-----END CERTIFICATE-----\n";
const char* certificate =
    "-----BEGIN CERTIFICATE-----\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "-----END CERTIFICATE-----\n";
const char* privateKey =
    "-----BEGIN RSA PRIVATE KEY-----\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "-----END RSA PRIVATE KEY-----\n";

WiFiClientSecure httpsClient;
PubSubClient mqttClient(httpsClient);

long messageSentAt = 0;
int dummyValue = 0;
char pubMessage[128];

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // For WiFi Error
  WiFi.disconnect(true);
  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_awsiot() {
  httpsClient.setCACert(rootCA);
  httpsClient.setCertificate(certificate);
  httpsClient.setPrivateKey(privateKey);
  mqttClient.setServer(awsEndpoint, awsPort);
  mqttClient.setCallback(mqttCallback);
}

void connect_awsiot() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32-device";
    // clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying＿
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received. topic=");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print("\n");
}

void setup() {
  // Initialize the M5Stack object
  M5.begin();

  delay(10000);
  setup_wifi();
  setup_awsiot();
}

void loop() {
  if (!mqttClient.connected()) {
    connect_awsiot();
  }

  // subscribeのトピックを指定。これがないとmqttCallbackに入ってこない模様。
  // https://dotstud.io/blog/nefry-bt-connect-mqtt/
  mqttClient.subscribe(subTopic, 0);

  mqttClient.loop();

  long now = millis();
  if (now - messageSentAt > 5000) {
    messageSentAt = now;
    sprintf(pubMessage, "{\"message\": \"%d\"}", dummyValue++);
    Serial.print("Publishing message to topic ");
    Serial.println(pubTopic);
    Serial.println(pubMessage);
    mqttClient.publish(pubTopic, pubMessage);
    M5.Lcd.printf(pubMessage);
    Serial.println("Published.");
  }
  delay(5);
}
