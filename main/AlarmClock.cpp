// source: https://forum.arduino.cc/t/sketch-to-convert-milliseconds-to-hours-minutes-and-seconds-hh-mm-ss/636386/2

#ifndef AlarmClock_H_INCLUDED
#define AlarmClock_H_INCLUDED
#include <TimeLib.h>

class AlarmClock
{
  private: 
    int h, m;
    void secondsToHM (int sec) {
      m = sec / 60;
      h = m / 60;
      
      m %= 60;
      h %= 24;
    }
    
  public:
    void init(int timeAlarm) {
      secondsToHM(timeAlarm);     // convert seconds to Hour & Minute
    }
    
    bool alarmed (time_t timeNow) {
      return ( hour  (timeNow) == h && 
               minute(timeNow) == m && 
               second(timeNow) == 0 ); 
    }
};

#endif
