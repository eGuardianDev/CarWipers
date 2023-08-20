#include <EEPROM.h>

#include "CommonVariables.h"

#include "WebServerClass.h"
#include "CarWipes.h"
void setup() {

  SetupButtonsPins();
  Serial.begin(115200);


  delay(2000);
  
  if(digitalRead(WipeWhileHoldedButton) == HIGH && digitalRead(FullSwipeButton) == HIGH){
    SetupServer();
    Serial.println("Developer mode ON!");
    DeveloperMode = true;
  }
  delay(2000);
  SetupWiper();
  Serial.println("Finished initialization");
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