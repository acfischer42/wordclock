#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "time.h"
#include "grid.h"
#include "utcOffset.h"

void Time::setup() {
  Time::ntpClient.begin();
  Time::ntpClient.update();
}

void Time::loop() {
//Serial.println("Time::loop0");
//Time::ntpClient.update();
//Serial.println("Time::loop1");
  int h = Time::ntpClient.getHours();
  int m = Time::ntpClient.getMinutes();
  //int h = Time::ntpClient.getMinutes();
  //int m = Time::ntpClient.getSeconds();

//Serial.println("Time::loop2");
  if (h == 3){
    //Time::ntpClient.begin();
    //Time::ntpClient.update();

  }
  if(m != Time::minute) {
    if(m == 0 && h == Time::hour) {
      h = (h + 1) % 24;
    }

    Time::hour = h;
    Time::minute = m;
    Serial.println("grid::settime::in time.cpp");
    Grid::setTime(Time::hour, Time::minute);

    if (Config::automatic_timezone) {
      UtcOffset::updateLocalizedUtcOffset();
      Time::ntpClient.setTimeOffset(Config::timezone);
    }
  }
}

int Time::hour = -1;
int Time::minute = -1;
WiFiUDP Time::udp;
NTPClient Time::ntpClient = NTPClient(Time::udp);
