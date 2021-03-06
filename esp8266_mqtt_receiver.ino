#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 

const char* ssid     = "Freebox-1BF387";
const char* password = "reformator*-adaquemus2-vineias-saporata29";
const char* mqttServer = "192.168.1.30";
const int mqttPort = 1883;
const char* mqttUser = "chauffage";
const char* mqttPassword = "chauffage";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  // Lock power supply at button press
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");  
    } else {
       Serial.print("failed with state ");
       Serial.print(client.state());
       delay(1500);
    }
  }
  client.subscribe("chauffage");
  client.publish("chauffage", "hello"); 
  
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D2, LOW);
  
  Serial.println();
  Serial.println("-----------------------");
}
 
void loop() {
  client.loop();
}



  
