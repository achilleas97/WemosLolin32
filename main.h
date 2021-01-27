#include "DHT.h"
#include "ThinkSmartFarm.h"
#include "Parameter.h"

#define DHTPIN 17
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int hygrometer;

int maxTemperature = 38;           
int minTemperature = 5;
int maxHumidity = 90;
int minHumidity = 10;
int maxHygrometer = 90;
int minHygrometer = 0;

void setup()
{
    Serial.begin(115200);
    dht.begin(); 
    ConnectWifi();
}

void loop()
{
  hygrometer = analogRead(13); 
  hygrometer = constrain(hygrometer,400,1023);
  hygrometer = map(hygrometer,400,1023,100,0);
  
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();  
  
  if(isnan(temperature) || isnan(humidity)){
    Serial.println("Failed to read DHT11");
  }else{
   int action = 0;
   if(temperature > maxTemperature){
    action = 1;
    bot.sendMessage(CHAT_ID, "Max Temperature! Check to your profile", "");
   }else if(temperature < minTemperature){
    action = 2;
    bot.sendMessage(CHAT_ID, "Min Temperature! Check to your profile", "");
   }else if(humidity > maxHumidity){
    action = 3;
    bot.sendMessage(CHAT_ID, "Max Humidity! Check to your profile", "");
   }else if(humidity < minHumidity){
    action = 4;
    bot.sendMessage(CHAT_ID, "Min Humidity! Check to your profile", "");
   }else if(hygrometer > maxHygrometer){
    action = 5;
    bot.sendMessage(CHAT_ID, "Max Hygrometer! Check to your profile", "");
   }else if(hygrometer < minHygrometer){
    action = 6;
    bot.sendMessage(CHAT_ID, "Min Hygrometer! Check to your profile", "");
   }
   SendData(temperature, humidity, hygrometer, action);   
  }  
  delay(40000);
}
