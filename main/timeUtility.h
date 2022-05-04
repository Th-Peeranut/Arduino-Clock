#include <Arduino.h>

// source: https://forum.arduino.cc/t/convert-seconds-variable-into-hours-minutes-seconds/273112/2
String displayDigits(int digits) {  
  if (digits < 10) {
    return "0" + String(digits);
  }
  return String(digits);
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial.print('0');
    Serial.print(val);
    Serial.print(delim);
    return;
}

// Print time (and date) given a time_t value
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
    Serial.print(dayShortStr(weekday(t)));
    Serial.print(' ');
    printI00(day(t), ' ');
    Serial.print(monthShortStr(month(t)));
    Serial.print(' ');
    Serial.println(year(t));
    
    delay(1000);
}

// -----------------------------------------------------------------------

// source: https://forum.arduino.cc/t/solved-need-guidance-how-to-return-multiple-values-from-one-function/365761/4
uint8_t* secondsToHMS(unsigned long sec) {
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
