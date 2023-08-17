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
  server.onNotFound(handle_NotFound);
  delay(200);
  //start server
  server.begin();
  Serial.println("HTTP Server Started");
}

void ServerLoop(){
    server.handleClient();

}
