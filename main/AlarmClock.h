#include <BlynkSimpleEsp32.h>
#include <TimeAlarms.h>

AlarmId alarmClockId_1;
AlarmId alarmClockId_2;
AlarmId alarmClockId_3;

long alarmClock1_Input;
long alarmClock2_Input;
long alarmClock3_Input;

// source: https://forum.arduino.cc/t/solved-need-guidance-how-to-return-multiple-values-from-one-function/365761/4
uint8_t* _secondsToHMS(unsigned long sec) {
  unsigned long s = sec % 60;
  unsigned long m = sec / 60;
  unsigned long h = m / 60;
  
  m %= 60;
  h %= 24;

  static uint8_t values[3];
  values[0] = h;
  values[1] = m;
  values[2] = s;
  return values;
}

void alarmClock1_complete() {
  Blynk.virtualWrite(V3, 0);    // set On_Off button to waiting for restarting
}

void alarmClock2_complete() {
  Blynk.virtualWrite(V5, 0);    // set On_Off button to waiting for restarting
}

void alarmClock3_complete() {
  Blynk.virtualWrite(V7, 0);    // set On_Off button to waiting for restarting
}

void alarmClock1_setup() {
  uint8_t* HMS = _secondsToHMS(alarmClock1_Input);               
  alarmClockId_1 = Alarm.alarmRepeat(HMS[0], HMS[1], HMS[2], alarmClock1_complete);
  Blynk.virtualWrite(V3, 1);    // Alarm Clock 1 On
}

void alarmClock2_setup() {
  uint8_t* HMS = _secondsToHMS(alarmClock2_Input);               
  alarmClockId_2 = Alarm.alarmRepeat(HMS[0], HMS[1], HMS[2], alarmClock2_complete);
  Blynk.virtualWrite(V5, 1);    // Alarm Clock 2 On
}

void alarmClock3_setup() {
  uint8_t* HMS = _secondsToHMS(alarmClock3_Input);               
  alarmClockId_3 = Alarm.alarmRepeat(HMS[0], HMS[1], HMS[2], alarmClock3_complete);
  Blynk.virtualWrite(V7, 1);    // Alarm Clock 3 On
}

void alarmClock1_switch(int alarmClock1_Button) {
  if (alarmClock1_Input == NULL || alarmClock1_Input == 0) {
    Blynk.virtualWrite(V3, 0);                                  // stay in current state
    return;
  }
  else if (alarmClock1_Button == 0) {                           // Alarm Clock 1 Off
    Alarm.free(alarmClockId_1);
  }
}

void alarmClock2_switch(int alarmClock2_Button) {
  if (alarmClock2_Input == NULL || alarmClock2_Input == 0) {
    Blynk.virtualWrite(V5, 0);                                  // stay in current state
    return;
  }
  else if (alarmClock2_Button == 0) {                           // Alarm Clock 2 Off
    Alarm.free(alarmClockId_2);
  }
}

void alarmClock3_switch(int alarmClock3_Button) {
  if (alarmClock3_Input == NULL || alarmClock3_Input == 0) {
    Blynk.virtualWrite(V7, 0);                                  // stay in current state
    return;
  }
  else if (alarmClock3_Button == 0) {                           // Alarm Clock 3 Off
    Alarm.free(alarmClockId_3);
  }
}
