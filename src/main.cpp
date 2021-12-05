/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "cWifi.h"

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;
int pin_led = 2;
int pin_button = 0;
uint8_t button_state = 0;
cWifi wifi;

void setup()
{
    Serial.begin(9600);
    pinMode(pin_led, OUTPUT);
    // pinMode(pin_button, INPUT);

    wifi.begin();
   
}

void loop()
{

    // Send an HTTP POST request depending on timerDelay
    if ((millis() - lastTime) > timerDelay)
    {
        //Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
                  // ======================================================
            // ======================================================
            WiFiClient client;
            HTTPClient http;
    
            // Your Domain name with URL path or IP address with path
            button_state = digitalRead(pin_button);
            Serial.print("Button state : ");
            Serial.println(button_state);
            
             // update button state
            // String serverPath = serverName + "update";
            // Your Domain name with URL path or IP address with path
            http.begin(client, serverName); //serverPath.c_str());

            // Send HTTP GET request
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            String postData = "button_state=" + String(button_state)+"&";
            int httpResponseCode = http.POST(postData);
            String payload = http.getString(); 
            if (httpResponseCode == 200)
            {
                Serial.print("HTTP POST response : ");
                Serial.println(httpResponseCode);
                Serial.println(payload); //Print request response payload 

            }
            else
            {
                Serial.println("HTTP error code -  bad post");
            }
            // Free resources
            http.end();
           
        }
        else
        {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}