#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ESP8266WebServer.h"

ESP8266WebServer server(80);
const char* ssid     = "chauffage";

// Temps de chauffage en minutes
int chauffage;
long timing ;

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html><html><body>
<h2>Reglage du temps de chauffage (minutes)<h2>
<form action="/action_page">
  Chauffage :<br>
  <input type="text" name="chauffage" value="">
  <br><br>
  <input type="submit" value="Submit">
</form></body></html>
)=====";

void setup() {
  Serial.begin(115200);
  getHeatingTime();
  timing = chauffage *1000*60;
  pinMode(D2, OUTPUT);
  
  WiFi.softAP(ssid);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);
  
  server.on("/chauffage",[](){
    server.send(200, "text/plain", "ok");
    Serial.println("connection reussie");
    digitalWrite(D2, HIGH);
    delay(timing);
    digitalWrite(D2, LOW);
    Serial.println("ok");
  });
  //server.on("/", handleRoot);      
  //server.on("/action_page", handleForm); 
  server.begin();
}
void loop() {
  server.handleClient();
}

void getHeatingTime (){
  bool result = SPIFFS.begin();
  Serial.println("SPIFFS opened: " + result);
  File chauffageFile = SPIFFS.open("/chauffage.txt", "r");
  if (!chauffageFile) {
    Serial.println("File doesn't exist yet. Creating it");
    File chauffageFile = SPIFFS.open("/chauffage.txt", "w");
    if (!chauffageFile) {
      Serial.println("file creation failed");
    }
    chauffage = 10;
    chauffageFile.println(chauffage);
    
  } 
  else {
    Serial.println ("Lecture du contenu du chauffage.txt");
    while(chauffageFile.available()) {
      String line = chauffageFile.readStringUntil('\n');
      Serial.println(line);
      chauffage = line.toInt();
    }
    Serial.println ("Fin du contenu du chauffage.txt");
    
  }
  chauffageFile.close();
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
void handleForm() {
  chauffage = server.arg("firstname").toInt(); 
  Serial.print("Nouveau temps de chauffage: ");
  Serial.println(chauffage);
  File chauffageFile = SPIFFS.open("/chauffage.txt", "w");
  chauffageFile.println(chauffage);  
  chauffageFile.close();
  timing = chauffage *1000*60;
  String s = "<a href='/'> Go Back </a>";
  server.send(200, "text/html", s); //Send web page
}
