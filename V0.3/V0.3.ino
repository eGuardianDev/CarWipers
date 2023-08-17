#include "WebServerClass.h"
#include "CarWipes.h"
#include "CommonVariables.h"
void setup() {

  SetupButtonsPins();
  Serial.begin(115200);

  delay(1000);
  
  if(digitalRead(WipeWhileHoldedButton) == HIGH && digitalRead(FullSwipeButton) == HIGH){
    SetupServer();
    Serial.println("Developer mode ON!");
    DeveloperMode = true;
  }

  SetupWiper();
}

void loop() {

  if(DeveloperMode == true){
    ServerLoop();
  }

  WipersLoop();
}

void SetupButtonsPins(){

  pinMode(WipeWhileHoldedButton,OUTPUT);
  pinMode(FullSwipeButton,OUTPUT);

}