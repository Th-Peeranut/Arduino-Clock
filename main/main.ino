#include "blynk.h"
//#include "RTC.h"
//#include "TimeRTC.h"

// Your WiFi credentials.
char ssid[] = "";
char password[] = "";

void setup() {
  Serial.begin(115200);
  setupBlynk(ssid, password);
//  setupRTC();
//  clockSetup();
}

void loop() {
  connectToBlynk();
//  connectRTC();
//  clockRun();
}
