// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLZ8kxGcuI"
#define BLYNK_DEVICE_NAME "RTC LED Clock"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <TimeLib.h>
#include <WidgetRTC.h>

#include <WidgetTerminal.h>

//#include <TimeInputParam.h>

/* MCP79412RTC Lib */
#include "timeUtility.h"
//#include "alarmClock.h"
#include <TimeLib.h>
#include <MCP79412RTC.h>
MCP79412RTC RTC;

#include "AlarmClock.cpp"
AlarmClock alarmC;
/*                 */

char auth[] = BLYNK_AUTH_TOKEN;


BlynkTimer timer;

WidgetRTC widgetRTC;
WidgetTerminal terminal(V2);

BLYNK_WRITE(V2) {
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'");
    terminal.println("I said: 'Polo'");
  } else {
    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

// Alarm Clock input
BLYNK_WRITE(V3) {
  long alarmClockInput = param[0].asLong();  // unix time (seconds)

  alarmC.init(alarmClockInput);
}
BLYNK_WRITE(V4) {
  TimeInputParam t(param);

  // Process start time
  if (t.hasStartTime()) {
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
  } else if (t.isStartSunrise()) {
    Serial.println("Start at sunrise");
  } else if (t.isStartSunset()) {
    Serial.println("Start at sunset");
  }

  // Process stop time
  if (t.hasStopTime()) {
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute() + ":" +
                   t.getStopSecond());
  } else if (t.isStopSunrise()) {
    Serial.println("Stop at sunrise");
  } else if (t.isStopSunset()) {
    Serial.println("Stop at sunset");
  }

  // Process timezone
  // Timezone is already added to start/stop time
  Serial.println(String("Time zone: ") + t.getTZ());

  // Get timezone offset (in seconds)
  Serial.println(String("Time zone offset: ") + t.getTZ_Offset());

  // Process weekdays (1. Mon, 2. Tue, 3. Wed, ...)
  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      Serial.println(String("Day ") + i + " is selected");
    }
  }

  Serial.println();
}

/* source: https://examples.blynk.cc/?board=ESP32&shield=ESP32%20WiFi&example=Widgets%2FRTC */
void clockDisplay() {
  if (timeStatus() != timeSet) {                                  // TimeLib.timeStatus
    setTime(hour(), minute(), second(), day(), month(), year());  // set the system time to current date & time
    RTC.set(now());                                               // set the RTC from the system time
  }
  
  String displayCurrentTime = String( displayDigits( hour() ) ) + ":" + displayDigits( minute() ) + ":" + displayDigits( second() );
  String displayCurrentDate = String( day() ) + "-" + month() + "-" + year();

  Blynk.virtualWrite(V0, displayCurrentTime);  // Send time to the App
  Blynk.virtualWrite(V1, displayCurrentDate);  // Send date to the App
}

BLYNK_CONNECTED() {
  widgetRTC.begin();    // Synchronize time on connection
}

void setupBlynk(char* ssid, char* pass) {
  Blynk.begin(auth, ssid, pass);
 
  setSyncInterval(10 * 60); // TimeLib.h Sync interval in 10*60 seconds (10 minutes)

  timer.setInterval(1000L, clockDisplay);   // Display digital clock every 1 seconds

  terminal.clear();   // Clear the terminal content
}

void connectToBlynk() {
  Blynk.run();
  timer.run();

  if ( alarmC.alarmed(now()) ) {
    Serial.println("Warning !!!");
    delay(1000);
    return;
  }
  

}
