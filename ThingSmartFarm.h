#include <WiFi.h> 
#include "Parameter.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "Parameter.h"

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* token    = SECRET_TOKEN;
const char* host     = "";

void SendData(float temperature, float humidity, float hygrometer, int action);

WiFiClientSecure telegram;
UniversalTelegramBot bot(BOTtoken, telegram);

void ConnectWifi(){
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());   
}

void SendData(float temperature, float humidity, float hygrometer, int action){
  // Use WiFiClient class to create TCP connections
  WiFiClient client;         
  
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
          
  client.print(String("GET /...........//path//..............?") + 
                          ("&temperature=") + temperature +
                          ("&humidity=") + humidity + ("&hygrometer=") + hygrometer + ("&action=")+ action + ("&token=") + token +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line); 
  }
  
  Serial.println("closing connection");
}  
