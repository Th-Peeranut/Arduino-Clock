#include <BlynkSimpleEsp32.h>
#include <Countimer.h>      // https://github.com/Th-Peeranut/Countimer

Countimer countUpTimer;

void countUpTimerDisplay() {
  Blynk.virtualWrite(V8, countUpTimer.getCurrentTime_MMSSss());   // Send current count up time to the App
  Serial.println(countUpTimer.getCurrentMilliSeconds());
}

void countUpTimerComplete() {
  Blynk.virtualWrite(V8, "00:00:00");
  Blynk.virtualWrite(V9, 0);              // set Start_Pause button to waiting for restarting
  Blynk.virtualWrite(V10, 0);             // set Reset button to waiting for restarting
}

void countUpTimerButton_StartPause(int countUpStart_PauseButton) {
  countUpTimer.setCounter(1, 0, 0, countUpTimer.COUNT_UP, countUpTimerComplete);

  if (countUpStart_PauseButton == 1) {                    // Start button clicked
    countUpTimer.setInterval(countUpTimerDisplay, 100);   // Display current count up time every 0.1 seconds
    Blynk.virtualWrite(V10, 1);                           // enable Reset button
    countUpTimer.start();
  } else if (countUpStart_PauseButton == 0) {             // Pause button clicked
    countUpTimer.pause();
  }
}

void countUpTimerButton_Reset(int countUpResetButton) {
  if (countUpResetButton == 1) {
    Blynk.virtualWrite(V10, 0);           // stay in current state
    return;
  }
  else if (countUpResetButton == 0){      // Reset button clicked  
    countUpTimerComplete();
    countUpTimer.stop();
  }
}
