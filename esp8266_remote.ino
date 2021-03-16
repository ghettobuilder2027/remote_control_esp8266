// recepteur : CC:50:E3:08:08:04
// commande :  CC:50:E3:08:0F:95

#include <ESP8266WiFi.h>
#include <espnow.h>

const char* ssid     = "chauffage";

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xCC, 0x50, 0xE3, 0x08, 0x08, 0x04};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  bool a;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  pinMode(D2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connection Successful");
  digitalWrite(D2, HIGH);
  delay(1000);
  digitalWrite(D2, LOW);
    

  
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    myData.a = true;

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  }
}
