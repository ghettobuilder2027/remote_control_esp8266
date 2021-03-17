#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid     = "chauffage";
const char* serverChauffage = "http://192.168.4.1/chauffage";
String retour;

IPAddress ip(192, 168, 1, 12); 
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "--"; 
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}

void setup() {
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  
  Serial.begin(115200);
  WiFi.mode( WIFI_STA );
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connection Successful");

  if(WiFi.status()== WL_CONNECTED){
      retour = httpGETRequest(serverChauffage);
      Serial.println(retour);
      if (retour == "ok") {
        digitalWrite(D2, LOW);
      }
    }  
}

void loop() {
}
