#include <BlynkSimpleEsp32.h>
#include <Countimer.h>      // https://github.com/Th-Peeranut/Countimer
#include "timeUtility.h"

Countimer countdownTimer;
long countDownInput;

void countdownTimerDisplay() {
  Blynk.virtualWrite(V12, countdownTimer.getCurrentTime());  // Send current countdown time to the App
}

void countdownTimerComplete() {
  Blynk.virtualWrite(V12, "HH:MM:SS");    
  Blynk.virtualWrite(V13, 0);             // set Start_Stop button to waiting for restarting
  Blynk.virtualWrite(V14, 0);             // set Pause_Continue button to waiting for restarting
}

void countdownTimerInput() {
  uint8_t* HMS = secondsToHMS(countDownInput);    // timeUtility.h

  countdownTimer.setCounter(HMS[0], HMS[1], HMS[2], countdownTimer.COUNT_DOWN, countdownTimerComplete); 

}

void countdownTimerButton_StartStop(int countdownStart_StopButton) {
  if (countDownInput == NULL || countDownInput == 0) {
    Blynk.virtualWrite(V13, 0);                                // stay in current state
    return;
  }
  else if (countdownStart_StopButton == 1) {                        // Start button clicked
    countdownTimer.setInterval(countdownTimerDisplay, 1000);   // Display current countdown time every 1 second
    countdownTimer.start();
  } 
  else if (countdownStart_StopButton == 0) {                   // Stop button clicked
    countdownTimerComplete();
    countdownTimer.stop();
  }
}

void countdownTimerButton_PauseContinue(int countdownPause_ContinueButton) {
  if (countDownInput == NULL || countDownInput == 0) {
    Blynk.virtualWrite(V14, 0);               // stay in current state
    return;
  }
  else if (countdownPause_ContinueButton == 1 &&         // Pause button clicked
      !countdownTimer.isStopped())                  // use isStopped because before starting timer, isStopped value is true
  {  
    countdownTimer.pause();
  } 
  else if (countdownPause_ContinueButton == 0 ) {   // Continue button clicked
    countdownTimer.start();
  } else {
    Blynk.virtualWrite(V14, 0);                     // stay in current state 
  }
}
