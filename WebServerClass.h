#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


//web handles
void handle_OnConntect();
void handle_Swipe();
void handle_NotFound();


//main system
void ConfigureSettings();
void SetupServer();
void ServerLoop();