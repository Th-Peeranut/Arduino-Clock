#include "blynk.h"

// Your WiFi credentials.
char ssid[] = "";
char password[] = "";

void setup() {
  Serial.begin(115200);
  setupBlynk(ssid, password);
}

void loop() {
  connectToBlynk();
}
