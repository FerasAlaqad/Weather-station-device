# Weather station device
 ESP32 + BME280 + SHT3x +  SSD1306 LCD + Blynk + buzzer +Button 

<p float="left">
<img src="https://user-images.githubusercontent.com/87244886/133886855-6ff87dc0-cb92-4ed5-94cb-04b97ac40d40.png" width="300" height="300">
<img src="https://user-images.githubusercontent.com/87244886/133886954-05181230-3186-45a1-866e-b30f81187312.png" width="300" height="300">
<img src="https://user-images.githubusercontent.com/87244886/133887043-9df97e09-710c-43ba-aa0c-2dc09ce92184.png" width="300" height="300">
</p>

This is libraries i used:  
#include <WiFi.h>  
#include <WiFiClient.h>  
#include <BlynkSimpleEsp32.h>  
#include <Adafruit_Sensor.h>  
#include <Adafruit_BMP280.h>  
#include <SHT3x.h>  
#include <Wire.h>  
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h>  
#include <WiFiManager.h>  
#include "ESP32TimerInterrupt.h"    

If you want to see pressure, temperature, and Humidity values on your phone you have to connect esp32 to wifi and you should download the Blynk application on your phone.
While you are choosing indicators in Blynk you should choose ports the same as i choosed in code.    

This device can connect to any wifi, wifi reset can be done by pressing the button for more than 3 seconds.   
You can reset esp32 wifi by connect your phone to the router will be started from esp32.

