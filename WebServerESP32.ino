#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "sensor_capacitivo.hpp"
#include "ultrasonico_si.hpp"
#include "sensor_de_ph.hpp"


WebServer server(80);             
 
void setup() {
  //Añadir inicialización de pines
  pinMode(pUltraSonicTriger, OUTPUT);
  pinMode(pUltraSonicEcho, OUTPUT);
  pinMode(pPh, INPUT);
  pinMode(pCapacitive1, INPUT);
  pinMode(pCapacitive2, INPUT);
  pinMode(pCapacitive2, INPUT);
  pinMode(pBombaAgua, OUTPUT);
  pinMode(pAlarm, OUTPUT);

  //Estado de outputs
  sBombaAgua= 0;

  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);
 
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/pump", handlePump);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  updateCapacitive(pCapacitive1, sCapacitive1);
  updateCapacitive(pCapacitive2, sCapacitive2);
  updatePh();
  updateUltrasonic();
  sBombaAgua= digitalRead(pBombaAgua);
  server.handleClient();
}

void handle_OnConnect() {
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", statusJson()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String statusJson(){
    String response = 
    String("{")+
        "\"pump\":"+ String(sBombaAgua)+","+
        "\"ultrasonic\":"+ String(sUltrasonic)+","+
        "\"capacitive1\":"+ String(sCapacitive1)+","+
        "\"capacitive2\":"+ String(sCapacitive2)+","+
        "\"'ph'\":"+ String(sPh)+
        
    "}"
    ;
    

    return response;
  
}

void handlePump(){
  sBombaAgua= !sBombaAgua;
}

void updateLimitAgua(){
  if(1.0*alturaMax/sUltrasonic *100 >limitAgua ){
    sAlarm=1;
   
  }
  else{
    sAlarm=0;
  }
   digitalWrite(pAlarm, sAlarm);
}

