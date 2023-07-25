#include "WebServerClass.h"
#include "CarWipes.h"
#include "CommonVariables.h"
void setup() {
  SetupButtonsPins();
  delay(1000);
  Serial.begin(115200);
 // if(digitalRead(WipeWhileHoldedButton) == HIGH && digitalRead(FullSwipeButton) == HIGH){
 // SetupServer();
 // Serial.println("Developer mode ON!");
 // DeveloperMode = true;
 // }
  SetupWiper();
}

void loop() {
  // put your main code here, to run repeatedly:
  // if(DeveloperMode == true){
  //   ServerLoop();
  // }
  WipersLoop();
}

void SetupButtonsPins(){
  pinMode(WipeWhileHoldedButton,OUTPUT);
  pinMode(FullSwipeButton,OUTPUT);
}