#include"config.h"
#include<FastLED.h>
#include<RTClib.h>
#include"Screen.h"
#include"Virtual_screen.h"
#include"Model_manager.h"
#include"Virtual_key.h"
#include"Scene_manager.h"

CRGB leds[SCREEN_NUM];
RTC_DS3231 rtc;
DateTime now_rtc_time;
Model_manager model_manager;
Hardware_key hardware_keys[4];

unsigned long aggregate_time=0;

//---
Virtual_screen loading;
Virtual_screen test(56);
//---

Screen screen;

void setup() {
  Wire.begin();

#ifdef DEBUG
  Serial.begin(115200);
  if (!rtc.begin()) {
    Serial.println("rtc.begin() fail");
  }
  if(rtc.lostPower()){      
    Serial.println("==== DS3231 DETECT POWER LOSS! ====");
  }
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
#endif

  pinMode(LED_PIN,OUTPUT);
  for(int i=0;i<4;i++)hardware_keys[i].init(i);
  screen.input();
  Scene_manager::rt()->init();

  //---
  loading.draw_loading();
  loading.show();
  // screen.show();
  test.draw_letter(0,0,'H',0x3f5df9);
  test.draw_letter(5,0,'E',0x505bed);
  test.draw_letter(10,0,'L',0x6359df);
  test.draw_letter(15,0,'L',0x7c56cd);
  test.draw_letter(20,0,'O',0x9452b9);
  test.draw_letter(29,0,'W',0xaa50a8);
  test.draw_letter(35,0,'O',0xc14d96);
  test.draw_letter(41,0,'R',0xd44a88);
  test.draw_letter(46,0,'L',0xe64879);
  test.draw_letter(51,0,'D',0xed4d6e);

  delay(5000);
}

void loop() {
  unsigned long begin_time=millis();

#ifdef DEBUG
  if(Serial.available()){
    String cmd=Serial.readStringUntil('\n');
    cmd.trim();
    if(cmd.startsWith("set")){
      int y,m,d,h,mi,s;
      if(sscanf(cmd.c_str(),"set %d,%d,%d,%d,%d,%d",&y,&m,&d,&h,&mi,&s)==6){
        rtc.adjust(DateTime(y,m,d,h,mi,s));
        Serial.printf("Set time successly\n");
      }
    }
  }

  // Serial.printf("########time:%lu########\n",begin_time);
  //hardware_keys[0].debug();
#endif

  now_rtc_time=rtc.now();
  for(int i=0;i<4;i++)hardware_keys[i].update();
  screen.update(begin_time-aggregate_time);
  Scene_manager::rt()->update();
  Scene_manager::rt()->draw();
  /*
  screen.update(begin_time-aggregate_time);
  screen.clear();
  screen.show();
  */
  //---

  aggregate_time=begin_time;
  //unsigned long finish_time=millis();
  //int wait_time=max(0,1000/FPS-(finish_time-begin_time));
  //delay(wait_time);
}
