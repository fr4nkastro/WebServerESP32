#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "sensor_capacitivo.hpp"
#include "ultrasonico_si.hpp"
#include "sensor_de_ph.hpp"


WebServer server(80);             
 
void setup() {


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
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  updateCapacitive(pCapacitive1, sCapacitive1);
  updateCapacitive(pCapacitive2, sCapacitive2);
  updatePh();
  updateUltrasonic();
  server.handleClient();
}

void handle_OnConnect() {

  server.send(200, "application/json", statusJson()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String statusJson(){
    String response = 
    String("{")+
        "\"ultrasonic\":"+ String(sUltrasonic)+","+
        "\"capacitive1\":"+ String(sCapacitive1)+","+
        "\"capacitive12\":"+ String(sCapacitive2)+","+
        "\"'ph'\":"+ String(sPh)+
        
    "}"
    ;
    

    return response;
  
}
