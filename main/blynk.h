// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLZ8kxGcuI"
#define BLYNK_DEVICE_NAME "RTC LED Clock"
#define BLYNK_AUTH_TOKEN ""
char auth[] = BLYNK_AUTH_TOKEN;

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <WidgetRTC.h>

BlynkTimer timer;
WidgetRTC widgetRTC;

/* communicate to MCP79411 module */
#include <MCP79412RTC.h>    // https://github.com/JChristensen/MCP79412RTC
MCP79412RTC RTC;
/* ------------------------------ */

/* TimeAlarms library */
#include "AlarmClock.h"
/* ------------------ */

/* Countimer libraries */
#include "countdownTimer.h"
#include "countUpTimer.h"
/* ------------------- */

// Alarm Clock 1 Input
BLYNK_WRITE(V2) {
  alarmClock1_Input = param[0].asLong();  // unix time (seconds)
  alarmClock1_setup();
}

// Alarm Clock 1 Button: On_Off
BLYNK_WRITE(V3) {
  int alarmClock1_Button = param.asInt();

  alarmClock1_switch(alarmClock1_Button);  
}

// Alarm Clock 2 Input
BLYNK_WRITE(V4) {
  alarmClock2_Input = param[0].asLong();  // unix time (seconds)
  alarmClock2_setup();
}

// Alarm Clock 2 Button: On_Off
BLYNK_WRITE(V5) {
  int alarmClock2_Button = param.asInt();

  alarmClock2_switch(alarmClock2_Button);  
}

// Alarm Clock 3 Input
BLYNK_WRITE(V6) {
  alarmClock3_Input = param[0].asLong();  // unix time (seconds)
  alarmClock3_setup();
}

// Alarm Clock 3 Button: On_Off
BLYNK_WRITE(V7) {
  int alarmClock3_Button = param.asInt();

  alarmClock3_switch(alarmClock3_Button);  
}

// Count Up Timer Button: Start_Pause
BLYNK_WRITE(V9) {
  int countUpStart_PauseButton = param.asInt();

  countUpTimerButton_StartPause(countUpStart_PauseButton);
}

// Count Up Timer Button: Reset
BLYNK_WRITE(V10) {
  int countUpResetButton = param.asInt();

  countUpTimerButton_Reset(countUpResetButton);
}

// Countdown Timer input
BLYNK_WRITE(V11) {
  countDownInput = param[0].asLong();             // unix time (seconds)

  countdownTimerInput();
}

// Countdown Timer Button: Start_Stop
BLYNK_WRITE(V13) {
  int countdownStart_StopButton = param.asInt();
  
  countdownTimerButton_StartStop(countdownStart_StopButton);
}

// Countdown Timer Button: Pause_Continue
BLYNK_WRITE(V14) {
  int countdownPause_ContinueButton = param.asInt();

  countdownTimerButton_PauseContinue(countdownPause_ContinueButton);
}

BLYNK_CONNECTED() {
  widgetRTC.begin();                    // Synchronize time on connection
  Blynk.syncAll();                      // Request server to re-send latest values for all pins on board

  // if system time is not set & synced
  if (timeStatus() != timeSet) {                                  // TimeLib.timeStatus
    setTime(hour(), minute(), second(), day(), month(), year());  // set the system time to current date & time
    RTC.set(now());                                               // set the RTC from the system time
  }

  // set default Alarm Clock 1
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);

  // set default Alarm Clock 2
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V5, 0);

  // set default Alarm Clock 3
  Blynk.virtualWrite(V6, 0);
  Blynk.virtualWrite(V7, 0);

  // set default Count Up Timer 
  Blynk.virtualWrite(V8, "00:00:00");   
  Blynk.virtualWrite(V9, 0);
  Blynk.virtualWrite(V10, 0);

  // set default Countdown Timer
  Blynk.virtualWrite(V11, 0);    
  Blynk.virtualWrite(V12, "HH:MM:SS"); 
  Blynk.virtualWrite(V13, 0); 
  Blynk.virtualWrite(V14, 0);        
}

/* source: https://examples.blynk.cc/?board=ESP32&shield=ESP32%20WiFi&example=Widgets%2FRTC */
void clockDisplay() {
  String displayCurrentTime = String( displayDigits( hour() ) ) + ":" + displayDigits( minute() ) + ":" + displayDigits( second() );
  String displayCurrentDate = String( day() ) + "-" + month() + "-" + year();

  Blynk.virtualWrite(V0, displayCurrentTime);  // Send time to the App
  Blynk.virtualWrite(V1, displayCurrentDate);  // Send date to the App
}

// setup method
void setupBlynk(char* ssid, char* pass) {
  Blynk.begin(auth, ssid, pass);
 
  setSyncInterval(10 * 60);                 // TimeLib.h Sync interval in 10*60 seconds (10 minutes)

  timer.setInterval(1000L, clockDisplay);   // Display digital clock every 1 seconds
}

// loop method
void connectToBlynk() {
  Blynk.run();
  timer.run();

  Alarm.delay(1000);

  countUpTimer.run();
  countdownTimer.run();
}
