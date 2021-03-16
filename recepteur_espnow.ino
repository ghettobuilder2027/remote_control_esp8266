#include <ESP8266WiFi.h>
#include <espnow.h>

const char* ssid     = "ESP8266";

void setup() {
  
  pinMode(D2, OUTPUT);
  
  Serial.begin(115200);
  WiFi.softAP("chauffage");
  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);
  
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  
}


typedef struct struct_message {
    bool a;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Bool: ");
  Serial.println(myData.a);
  if (myData.a == true) {
      digitalWrite(D2, HIGH);
      delay(200);
      digitalWrite(D2, LOW);
  }
}
 

void loop() {
  
}