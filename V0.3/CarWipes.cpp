#include "CarWipes.h"
#include "CommonVariables.h"

#include <EEPROM.h>

bool CheckTimerFinished();
void StartTimer();
// varibles template
//WipesToDo = 0;
//MaxWipes = 3 ;
//
// ConstantLoopWiping = false;
// WipesToDo = 0;
// SwipesAreSuppostToMove = false;
//
int StartedFromMilli2 = 0;
bool FullSwipePressed = false;
// FullSwipeButton = 12 ;
// ConstantSwippingButton = 13 ;
// WipeWhileHoldedButton = 15 ;


// timming variables
int StartedFromMilli;
int HoldedFor = 0;
int StartedToHoldFrom = 0;

bool WipeWhileHoldedSwipePressed;
//Main functions
void AddFullWipe() {
  if (WipesToDo < MaxWipes) {

    if (DeveloperMode == true) {
      Serial.println("Added swipe");
    }

    WipesToDo += 1;
    delay(100);
    return;
  }
}

void SetupWiper() {
  pinMode(WipersPin, OUTPUT);
  TurnOffWipe();
  int eepromData = 0;
  EEPROM.get(0, eepromData);
  if(eepromData <300 ){
    Serial.println("Error: Timing for swippes to slow; assign new value to EEPROM");
  }
  else{
    WaitMilliSeconds = eepromData;
  }
  if (DeveloperMode) {
    Serial.println("Setting up wipers");
  }
  delay(100);
}


void ConstantWipingON() {
  ConstantLoopWiping = true;
  delay(100);
}
void ConstantWipingOFF() {
  ConstantLoopWiping = false;
  delay(100);
}

// TOOD implemenmt:  WipeWhileHoldedButton = 15 ;


void FullWipeButton() {
  if (digitalRead(FullSwipeButton) == HIGH && FullSwipePressed == false) {
    FullSwipePressed = true;

    delay(100);
    return;
  } else if (digitalRead(FullSwipeButton) == LOW && FullSwipePressed == true) {
    FullSwipePressed = false;


    AddFullWipe();
    delay(100);
    return;
  }


  if (digitalRead(WipeWhileHoldedButton) == HIGH && WipeWhileHoldedSwipePressed == false) {

    WipeWhileHoldedSwipePressed = true;

    if (WipesAreSuppostToMove == false) {
      WipesAreSuppostToMove = true;
      Serial.println("Swipping is activated");
      TurnOnWipe();
      StartedToHoldFrom = millis();
    }
    return;

  } else if (digitalRead(WipeWhileHoldedButton) == LOW &&  WipeWhileHoldedSwipePressed == true) {

    WipeWhileHoldedSwipePressed = false;
    Serial.println("Swipping button is Released");
    if (StartedToHoldFrom > 0) {
      WipesAreSuppostToMove = false;
      TurnOffWipe();
      HoldedFor += millis() - StartedToHoldFrom;
      Serial.print("The button was holded for: ");
      Serial.println(HoldedFor);
      while (HoldedFor >= 1500) {
        HoldedFor -= 1500;
      }
      Serial.print("Calibrated time: ");
      Serial.println(HoldedFor);
    }
  }
}

int TimerMilliseconds = 1;
void WipersLoop() {
  // Serial.print("started form : ");
  // Serial.println(TimerMilliseconds);
  // Serial.print("started form : ");
  // Serial.println(HoldedFor);
  FullWipeButton();
  if (WipeWhileHoldedSwipePressed == true) { return; }
  if (WipesToDo > 0) {
    // if(cat == false){
    //   StartTimer();
    //   cat = true;
    // }

    // Serial.println("===================");
    // Serial.println("Time needed");
    // Serial.println(TimerMilliseconds);
    // Serial.println("Current Time:");
    // Serial.println(millis());
    // Serial.print("Is it ended");
    // Serial.println(CheckTimerFinished());
    // Serial.println("===================\n");
    
    //delay(250);


    Serial.println("Spinning is activated, because the button was clicked.");

    // Serial.println(WipesAreSuppostToMove);
    if (WipesAreSuppostToMove == false) {
      Serial.println(" ======== Started to spin =========");
      StartTimer();
      WipesAreSuppostToMove = true;
      TurnOnWipe();
      delay(100);
      return;
    }
    else if (CheckTimerFinished() == true && WipesAreSuppostToMove == true) {
      Serial.println(" ======== Stop   spin =========");
      TurnOffWipe();
      // if(HoldedFor >0 ){
      // TimerMilliseconds = TimerMilliseconds - HoldedFor;
      // HoldedFor = 0;
      // }
      Serial.print("Finished at miliseconds: ");
      Serial.println(millis());
      WipesAreSuppostToMove = false;
      WipesToDo--;
      delay(100);
      return;
    }
  }
  delay(100);
}

void StartTimer() {
  delay(100);
  TimerMilliseconds = millis();
  delay(100);
  return;
}
bool CheckTimerFinished() {
  delay(100);
  if (HoldedFor > 0) {
    Serial.print("Remvoing Second => ");
    Serial.println(HoldedFor);
    Serial.print("To wait => ");
    Serial.println(TimerMilliseconds);
    TimerMilliseconds = TimerMilliseconds - HoldedFor;
    HoldedFor = 0;
    Serial.print("To wait => ");
    Serial.println(TimerMilliseconds);
    Serial.print("Current time=> ");
    Serial.println(millis());
  }
  if (TimerMilliseconds + WaitMilliSeconds > millis()) {
    return false;
  }
  return true;
}

// Actions

void TurnOnWipe() {
  digitalWrite(WipersPin, LOW);
}
void TurnOffWipe() {
  Serial.println("Stopped");
  digitalWrite(WipersPin, HIGH);
}
