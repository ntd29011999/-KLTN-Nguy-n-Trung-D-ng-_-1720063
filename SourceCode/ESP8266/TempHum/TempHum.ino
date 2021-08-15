la
#include "DHT.h"
#include <WiFiManager.h>
#include <ESP8266WiFi.h>               
#include <ESP8266HTTPClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Daikin.h>
#include <IRutils.h>
#include "BaseOTA.h"
#include <assert.h>
#include <ArduinoJson.h>


// DHT11
#define DHTPIN 5 
#define DHTTYPE DHT11 
// LED VA QUAT
#define RELAY1PIN 0
#define LEDPIN 2

String nhietdo, doam, mota, postData;

// SENSOR nhiet do
DHT dht(DHTPIN, DHTTYPE); 
// Json parse
StaticJsonDocument<1024> doc;


void setup() {

    Serial.begin(115200);
    pinMode(RELAY1PIN, OUTPUT);    
    pinMode(LEDPIN, OUTPUT);        
  
    dht.begin(); 


  WiFiManager wifiManager;



  wifiManager.setConfigPortalTimeout(180);
  

  if(!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  } 


  Serial.println("connected...yeey :)");

    Serial.println("\n");
    Serial.println("Connection established!");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());    

}
void postDataTempHum(float h, float t){
      HTTPClient http; 
      nhietdo = String(t);
      doam = String(h);
      
      postData = "nhietdo=" + nhietdo + "&doam=" + doam + "&mota=" + mota;

      http.begin("http://ntd29011999.000webhostapp.com/insertdata.php");           
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");          
      int httpCode = http.POST(postData);  
      Serial.println("Values are, nhietdo = " + nhietdo + " and doam = "+ doam + " and mota = " +mota );
      if (httpCode == 200) { 
        Serial.println("Values uploaded successfully."); 
        Serial.println(httpCode); 
        String webpage = http.getString();   
        Serial.println(webpage + "\n");
      }

      else { 
        Serial.println(httpCode); 
        Serial.println("Failed to upload values. \n"); 
        http.end(); 
        return; 
        }
      http.end();
}



void getDataDevice(String &battat, String &chedo, String &led){     
//getdataDevice
      HTTPClient http; 
      http.begin("http://ntd29011999.000webhostapp.com/getdataDevice.php");             
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");           
 
      int httpCode = http.GET();   
      if (httpCode > 0) { 
        Serial.println("Values get successfully."); 
        Serial.println(httpCode); 
        String webpage = http.getString();   
        Serial.println(webpage + "\n");

 
        DeserializationError error = deserializeJson(doc, webpage);
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
      
        JsonArray array = doc.as<JsonArray>();
        for(JsonVariant v : array) {
          JsonObject obj = v.as<JsonObject>();
          battat = obj["battat"].as<String>();
          chedo = obj["chedo"].as<String>();
          led = obj["led"].as<String>();
          Serial.println(battat);
        }
        doc.clear();
      }

    else { 
        Serial.println(httpCode); 
        Serial.println("Failed to upload values. \n"); 
        http.end(); 
        return; 
        }
     http.end();
}

void loop() {
      String battat;
      String chedo;
      String led;

      getDataDevice(battat,chedo,led);

      float h = dht.readHumidity();
      float t = dht.readTemperature();
      Serial.println();
      if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" degrees Celcius, Humidity: ");
      Serial.println(h);
      if (t >= 23 && t <= 32){
          mota = "binh thuong";}
      else if (t>32){
          mota = "nong";
      }
      else mota = "lanh";
      if (chedo.equals("AUTO")){
         // DIEU KHIEN AUTO
         Serial.println("AUTO START");
         if (t >= 23 && t <= 32){          
          if(t <=27){
              digitalWrite(RELAY1PIN, HIGH);
              digitalWrite(LEDPIN, LOW);
              Serial.println("FAN: OFF\nLED: ON");     
          }
          else{
            digitalWrite(RELAY1PIN, HIGH);
            digitalWrite(LEDPIN, HIGH);
            Serial.println("FAN: OFF\nLED: OFF");
          }
        }
        else if (t > 32){   
            digitalWrite(RELAY1PIN, LOW);
            digitalWrite(LEDPIN, HIGH);
            Serial.println("FAN: ON\nLED: OFF");
        }
        else {
            digitalWrite(RELAY1PIN, HIGH);
            digitalWrite(LEDPIN, LOW);
            Serial.println("FAN: OFF\nLED: ON");
        }
      }
      
      else if (chedo.equals("MANUAL")){
        Serial.println("MANUAL START");
        if (battat.equals("ON")){
          digitalWrite(RELAY1PIN, LOW);
          Serial.println("FAN: ON");
        }
        else if (battat.equals("OFF")){
          digitalWrite(RELAY1PIN, HIGH);
          Serial.println("FAN: OFF");
        }
        if (led.equals("ON")){
          digitalWrite(LEDPIN, LOW);
          Serial.println("LED: ON");
        }
        else if(led.equals("OFF")){
          digitalWrite(LEDPIN, HIGH);
          Serial.println("LED: OFF");
        }
      }
 
      postDataTempHum(h,t);

    delay(60000); 

}








  
