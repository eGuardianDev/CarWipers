#include <EEPROM.h>

#include "WebServerClass.h"
#include "CommonVariables.h"
#include "CarWipes.h"

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
 

ESP8266WebServer server(80);

String HTML(){
  String msg= R"=====(
  
  <html>
  <head>
    <title> Wipers </title>
  </head>
  <body>
   <div style=" font-size:100px; margin:auto; width:50%;">

    <p>Activate wipers</p>
    <a href="/swipe"><button style=" padding:50px; font-size:50px; background-color:lightblue; border-radius:5px; ">swipe</button></a>
    
          <form action="/savedata" method="GET">
          <div>
            <label style=" padding:50px; font-size:50px" for="delayTiming">Change timing</label>
            <input style=" padding:50px; font-size:50px"  name="delayTiming" id="delayTiming" value="0" />
          </div>
          <div>
            <button style=" padding:50px; font-size:50px; background-color:lightblue; border-radius:5px; ">Update</button>
          </div>
        </form>


   </div>
  </body>
  </html>



 )=====";return msg;
}
//handle
void handle_OnConnect()
{
  Serial.println("Client Connected");
  server.send(200, "text/html", HTML()); 
}
void handle_Swipe()
{
  Serial.println("Client Connected");
  //FullSwipesButtonClicked();
  AddFullWipe();
  server.send(200, "text/html", HTML()); 
}
void handle_saveData()
{
  Serial.println("New Data Updated!");
  String delayTiming = server.arg("delayTiming");
  int delayTimingInt = 0;
  delayTimingInt = delayTiming.toInt();
  if(delayTimingInt < 0){
    Serial.println("Error making string to int while updating EEPROM");
    server.send(422, "text/html", "Error making string to int while updating EEPROM"); 
    return;

  }
  Serial.println(delayTiming);
  EEPROM.write(0, delayTimingInt);
  WaitMilliSeconds = delayTimingInt;
  EEPROM.commit();
  server.send(200, "text/html", HTML()); 
}
void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}



//main system
void ConfigureSettings(){
  //configures the system
  Serial.println("Starting ap");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  return;
}

void SetupServer() {
  Serial.begin(115200);
  DeveloperMode = true;
  //setup wifi
  ConfigureSettings ();
  delay(200);
 
  //Setup Server handles
  Serial.println("Starting Server");
  server.on("/",handle_OnConnect);
  server.on("/swipe",handle_Swipe);
  server.on("/savedata",handle_saveData);
  server.onNotFound(handle_NotFound);
  delay(200);
  //start server
  server.begin();
  Serial.println("HTTP Server Started");
}

void ServerLoop(){
    server.handleClient();

}
