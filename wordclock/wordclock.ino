#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "src/grid.h"
#include "src/wifi.h"
#include "src/types.h"
#include "src/color.h"
#include "src/config.h"
#include "src/dnd.h"
#include "src/led.h"
#include "src/time.h"
#include "src/httpServer.h"
#include "src/gui.h"
#include "src/controller.h"
//#define DATA_PIN 4
//CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  Serial.println();
  SPIFFS.begin();

  Config::load();

  Wifi::setup();
  HttpServer::setup();
  Led::setup();
  Time::setup();

  Grid::setTime(Time::hour, Time::minute);

  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  Time::loop();
  HttpServer::loop();
  //Serial.println("here");
/*
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
*/
}
  
