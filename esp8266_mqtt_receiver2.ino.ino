#include <ESP8266WiFi.h>
#include <MQTT.h>

#define CLIENT_ID "client"
#define TOPIC "chauffage"
MQTT myMqtt(CLIENT_ID, "192.168.1.30", 1883);

const char* ssid     = "";
const char* password = "reformator*-adaquemus2-vineias-saporata29";

void myDataCb(String& topic, String& data){
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(data);
  digitalWrite(D2, HIGH);
  delay(2000);
  digitalWrite(D2, LOW);
  Serial.println("omg");
}
void myConnectedCb(){
  Serial.println("connected to MQTT server");
}
void myDisconnectedCb(){
  Serial.println("disconnected. try to reconnect...");
  delay(500);
  myMqtt.connect();
}
void myPublishedCb(){
  Serial.println("published.");
}


void setup() {
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  delay(200);
  digitalWrite(D2, LOW);
  Serial.begin(115200);
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to MQTT server");  
  // setup callbacks
  myMqtt.setUserPwd("chauffage","chauffage");
  myMqtt.onConnected(myConnectedCb);
  myMqtt.onDisconnected(myDisconnectedCb);
  myMqtt.onPublished(myPublishedCb);
  myMqtt.onData(myDataCb);
  
  Serial.println("connect mqtt...");
  myMqtt.connect();

  Serial.print("subscribe to topic...");
  myMqtt.subscribe(TOPIC);
  Serial.println(TOPIC);
  
  delay(10);
}

//
void loop() {
}
