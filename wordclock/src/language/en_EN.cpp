#include <Arduino.h>

#include "en_EN.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

int Grid_en_EN::time_day_ix = 0;

void Grid_en_EN::setTime(int hour, int minute) {
  if(hour == -1 || minute == -1) {
	return;
  }
Serial.println("grid_en_EN::settime");

  if(DND::active(hour, minute)) {
	for(int i = 0; i < NUM_LEDS; i++) {
	  Led::ids[i].setRGB(0, 0, 0);
	}

	FastLED.show();

	return;
  }

  int singleMinute = minute % 5;
  int hourLimit = 6;

  minute = (minute - (minute % 5));


  Serial.println("en_EN before");

  Serial.println(hour);
  Serial.println(minute);
  for(int i = 0; i < NUM_LEDS; i++) {
  Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }
//need to put logic to show afternoon / evening here
//int Grid_en_EN::time_day[12][6]

  if(hour == 0) {
    time_day_ix = 0;
  }
  if(hour >= 0 && hour <= 11) {
    time_day_ix = 1;
  }
  if(hour > 12 && hour < 18) {
    time_day_ix = 3;
  }
  if(hour == 12 && minute == 0) {
    time_day_ix = 2;
  }
  if(hour == 12 && minute > 1 ) {
    time_day_ix = 3;
  }
  if(hour >= 19 && hour <= 21) {
    time_day_ix = 4;
  }
  if(hour >= 22) {
    time_day_ix = 5;
  }
  Serial.println(time_day_ix);

  if(minute >= 35) {
  hour += 1;
  }

  for(int i = 0; i < 14; i++) {
  if(Grid_en_EN::time_day[time_day_ix][i] >= 0) {
    Led::ids[Led::getLedId(Grid_en_EN::time_day[time_day_ix][i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);

  }
  }

  minute = minute / 5;
  hour = hour % 12;
    Serial.println("en_EN after");
  Serial.println(hour);
  Serial.println(minute);





  for(int i = 0; i < 5; i++) {

	Led::ids[Led::getLedId(Grid_en_EN::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }

// if noon skip hours and Minutes
  if (time_day_ix != 2) {
    for(int m = 0; m < 15; m++) {
	     if(Grid_en_EN::time_minutes[minute][m] >= 0) {
         //Serial.println(Grid_en_EN::time_minutes[minute][m]);
         Led::ids[Led::getLedId(Grid_en_EN::time_minutes[minute][m])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	      }
    }


    // if midnight skip Hours


    if(hour == 1 && minute == 0) {
	     hourLimit = 3;
    }

    for(int h = 0; h < hourLimit; h++) {
	     if(Grid_en_EN::time_hours[hour][h] >= 0) {
	        Led::ids[Led::getLedId(Grid_en_EN::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	      }
    }

  }
/*
Serial.println("GRID_SINGLE_MINUTES");
Serial.println(singleMinute);
  if(GRID_SINGLE_MINUTES == 1) {
	// single minutes
	for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
    Serial.println(s);
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  } else {
	for(int s = 0; s < singleMinute; s++) {
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }
*/
  //FastLED.setBrightness(Config::brightness * 255);
  FastLED.setBrightness(50);

  FastLED.show();
}

int Grid_en_EN::time_it_is[5] = {0, 1, 3, 4,-1}; // it is

int Grid_en_EN::time_minutes[12][15] = {
  { -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1}, // uhr
  { 16,  17,  18,  19,  32,  33,  34,  35,  -1,  -1,  -1,  -1, -1, -1, -1}, // five past
  {  6,   7,   8,  32,  33,  34,  35,  -1,  -1,  -1,  -1,  -1, -1, -1, -1}, // ten past
  { 22,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35, -1, -1, -1}, // a quarter past
  {  9,  10,  11,  12,  13,  14,  32,  33,  34,  35,  -1,  -1, -1, -1, -1}, // twenty past
  {  9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  32, 33, 34, 35}, // twenty-five past - needs hour adjust
  { 21,  22,  23,  24,  32,	 33,	34,  35,  -1,  -1,  -1,  -1, -1, -1, -1}, // half "past" needs hour adjust
  {  9,	 10,	11,	 12,	13,	 14,  15,  16,	17,	 18,	19,  35, 36, -1, -1}, // twenty-five to
  {  9,	 10,	11,	 12,	13,	 14,  35,  36,  -1,  -1,  -1,  -1, -1, -1, -1}, // twenty to
  { 22,  25,	26,	 27,	28,  29,	30,	 31,  35,  36,  -1,  -1, -1, -1, -1}, // a quarter to
  {  6,	  7,	 8,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1}, // ten to
  { 16,	 17,	18,	 19,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1, -1, -1, -1}  // five to
};

int Grid_en_EN::time_hours[12][6] = {
  {  80,	81,	 82, 	83,	84,	85}, // twelve
  {  40,  41,	 42,  -1, -1, -1}, // one
  {  38,	39,  40,  -1, -1, -1}, // two
  {  48,	49,  50,	51,	52, -1}, // three
  {  64,  65,  66,  67, -1, -1}, // four
  {  68,	69,	 70,	71, -1, -1}, // five
  {  58,	59,	 60,  -1, -1, -1}, // six
  {  72,	73,	 74,	75,	76, -1}, // seven
  {  42,	43,	 44,	45,	46, -1}, // eight
  {  76,	77,	 78,	79, -1, -1}, // nine
  {  61,	62,	 63,  -1, -1, -1}, // ten
  {  52,	53,	 54,	55,	56,	57}  // eleven
};

int Grid_en_EN::time_day[6][14] = {
  {  96, 97,	 98,	99,	100, 101,	102, 103,  -1,  -1,  -1,  -1,  -1,  -1}, // midnight
  {  90, 91, 	 93,	94,	 95, 104,	105, 106,	107, 108,	109, 110,  -1,  -1}, // in the morning
  { 117,118,	119, 120,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // noon
  {  90, 91, 	 93,	94,	 95, 112,	113, 114,	115, 116,	117, 118,	119, 120}, // in the afternoon
  {  90, 91, 	 93,	94,	 95, 121,	122, 123,	124, 125, 126, 127,  -1,  -1}, // in the evening
  {  87, 88,   99, 100,	101, 102,	103,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // at night
};
