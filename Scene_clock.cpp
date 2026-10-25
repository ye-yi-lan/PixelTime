#include<Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include "Scene_clock.h"
#include "Scene_manager.h"
#include "tools.h"

extern Hardware_key hardware_keys[4];
extern DateTime now_rtc_time;

Scene_clock::Scene_clock(){
  key_close.set_key(&hardware_keys[0]);
  key_back1.set_key(&hardware_keys[1]);
  key_back2.set_key(&hardware_keys[2]);
  key_back3.set_key(&hardware_keys[3]);

  key_close.set_click_function([&](){
    Scene_manager::rt()->changer(Scene_type::menu);
  });
  key_close.off();

  key_back1.set_click_function([&](){
    show_mode=(show_mode+1)%8;
    switch(show_mode){
      case 0:show_second=1,show_24h=1,show_smallsize=1;break;
      case 1:show_second=1,show_24h=0,show_smallsize=1;break;
      case 2:show_second=0,show_24h=1,show_smallsize=1;break;
      case 3:show_second=0,show_24h=0,show_smallsize=1;break;
      case 4:show_second=0,show_24h=1,show_smallsize=0;break;
      case 5:show_second=0,show_24h=0,show_smallsize=0;break;
      case 6:show_second=1,show_24h=1,show_smallsize=0;break;
      case 7:show_second=1,show_24h=0,show_smallsize=0;break;
    }
  });
  key_back1.off();

  key_back2.set_click_function([&](){
    brightness_usr+=0.05;
    if(brightness_usr>1)brightness_usr-=1;
  });
  key_back2.off();
  
  key_back3.set_click_function([&](){
    Scene_manager::rt()->changer(Scene_type::menu);
  });
  key_back3.off();
}

void Scene_clock::init(){
#ifdef DEBUG
  Serial.printf("****init scene: clock\n");
#endif
}

void Scene_clock::enter(){
#ifdef DEBUG
  Serial.printf("****enter scene: clock\n");
#endif
  key_close.on();
  key_back1.on();
  key_back2.on();
  key_back3.on();
}

void Scene_clock::update(){
#ifdef DEBUG
  // Serial.printf("=====scene:clock=====\n----update----\n");
#endif

  key_close.update();
  key_back1.update();
  key_back2.update();
  key_back3.update();

  int hour_buf=now_rtc_time.hour();
  int min_buf=now_rtc_time.minute();
  int second_buf=now_rtc_time.second();
  if(hour_buf>=0&&hour_buf<24)hour=hour_buf;
  if(min_buf>=0&&min_buf<60)min=min_buf;
  if(second_buf>=0&&second_buf<60)second=second_buf;

  if(auto_color){
    float a2=min/60.0;
    CHSV buf=mix_color(colors[hour],1.0-a2,colors[(hour+1)%24],a2);
    color_buf=buf;
    brightness_buf=brightnesses[hour]*(1-a2)+brightnesses[hour+1]*a2;
    brightness_buf=brightness_buf*brightness_usr;
  // return;//
  }else{
    brightness_buf=brightness_usr;
  }

  if(color_buf==0x000000){
    color=App_theme::color;
  }else{
    color=color_buf;
  }
  if(brightness_buf==0){
    brightness=App_theme::brightness;
  }else{
    brightness=brightness_buf;
  }
}

void Scene_clock::draw(){
#ifdef DEBUG
  // Serial.printf("----draw----\n");
#endif

  screen.clear();
  int t=hour;
  if(t>12)t-=12;
  
  if(show_second==1&&show_24h==1&&show_smallsize==1){//hh:mm:ss 24 小
    screen.draw_number(2,2,hour/10,color,brightness);
    screen.draw_number(6,2,hour%10,color,brightness);
    screen.draw_number(12,2,min/10,color,brightness);
    screen.draw_number(16,2,min%10,color,brightness);
    screen.draw_number(22,2,second/10,color,brightness);
    screen.draw_number(26,2,second%10,color,brightness);
    if(second%2){
      screen.draw_line(10,10,3,color,brightness);
      screen.draw_line(10,10,5,color,brightness);
      screen.draw_line(20,20,3,color,brightness);
      screen.draw_line(20,20,5,color,brightness);
    }
  }
  else if(show_second==1&&show_24h==0&&show_smallsize==1){//hh:mm:ss 12 小
    screen.draw_number(2,2,t/10,color,brightness);
    screen.draw_number(6,2,t%10,color,brightness);
    screen.draw_number(12,2,min/10,color,brightness);
    screen.draw_number(16,2,min%10,color,brightness);
    screen.draw_number(22,2,second/10,color,brightness);
    screen.draw_number(26,2,second%10,color,brightness);
    if(second%2){
      screen.draw_line(10,10,3,color,brightness);
      screen.draw_line(10,10,5,color,brightness);
      screen.draw_line(20,20,3,color,brightness);
      screen.draw_line(20,20,5,color,brightness);
    }
  }
  else if(show_second==0&&show_24h==1&&show_smallsize==1){//hh:mm 24 小
    screen.draw_number(7,2,hour/10,color,brightness);
    screen.draw_number(11,2,hour%10,color,brightness);
    screen.draw_number(17,2,min/10,color,brightness);
    screen.draw_number(21,2,min%10,color,brightness);
    if(second%2){
      screen.draw_line(15,15,3,color,brightness);
      screen.draw_line(15,15,5,color,brightness);
    }
  }
  else if(show_second==0&&show_24h==0&&show_smallsize==1){//hh:mm 12 小
    screen.draw_number(7,2,t/10,color,brightness);
    screen.draw_number(11,2,t%10,color,brightness);
    screen.draw_number(17,2,min/10,color,brightness);
    screen.draw_number(21,2,min%10,color,brightness);
    if(second%2){
      screen.draw_line(15,15,3,color,brightness);
      screen.draw_line(15,15,5,color,brightness);
    }
  }
  else if(show_second==0&&show_24h==1&&show_smallsize==0){//hh:mm 24 大
    screen.draw_number(5,1,hour/10,color,brightness,0);
    screen.draw_number(10,1,hour%10,color,brightness,0);
    screen.draw_number(17,1,min/10,color,brightness,0);
    screen.draw_number(22,1,min%10,color,brightness,0);
    if(second%2){
      screen.draw_line(15,15,3,color,brightness);
      screen.draw_line(15,15,5,color,brightness);
    }
  }
  else if(show_second==0&&show_24h==0&&show_smallsize==0){//hh:mm 24 大
    screen.draw_number(5,1,t/10,color,brightness,0);
    screen.draw_number(10,1,t%10,color,brightness,0);
    screen.draw_number(17,1,min/10,color,brightness,0);
    screen.draw_number(22,1,min%10,color,brightness,0);
    if(second%2){
      screen.draw_line(15,15,3,color,brightness);
      screen.draw_line(15,15,5,color,brightness);
    }
  }
  else if(show_second==1&&show_24h==1&&show_smallsize==0){//hh:mm:ss 24 大
    if(hour<10){
      screen.draw_number(3,1,hour%10,color,brightness,0);
    }else if(hour<20){
      screen.draw_liney(1,1,7,color,brightness);
      screen.draw_number(3,1,hour%10,color,brightness,0);
    }else{
      screen.draw_number(0,1,hour/10,color,brightness,0,1);
      screen.draw_number(4,1,hour%10,color,brightness,0,1);
    }
    screen.draw_number(10,1,min/10,color,brightness,0);
    screen.draw_number(15,1,min%10,color,brightness,0);
    screen.draw_number(22,1,second/10,color,brightness,0);
    screen.draw_number(27,1,second%10,color,brightness,0);
    if(second%2){
      screen.draw_line(8,8,3,color,brightness);
      screen.draw_line(8,8,5,color,brightness);
      screen.draw_line(20,20,3,color,brightness);
      screen.draw_line(20,20,5,color,brightness);
    }
  }
  else if(show_second==1&&show_24h==0&&show_smallsize==0){//hh:mm:ss 12 大
    if(t<10){
      screen.draw_number(3,1,t%10,color,brightness,0);
      screen.draw_number(10,1,min/10,color,brightness,0);
      screen.draw_number(15,1,min%10,color,brightness,0);
      screen.draw_number(22,1,second/10,color,brightness,0);
      screen.draw_number(27,1,second%10,color,brightness,0);
    }else{
      screen.draw_liney(2,1,7,color,brightness);
      screen.draw_number(4,1,t%10,color,brightness,0,1);
      screen.draw_number(11,1,min/10,color,brightness,0);
      screen.draw_number(16,1,min%10,color,brightness,0);
      screen.draw_number(23,1,second/10,color,brightness,0);
      screen.draw_number(28,1,second%10,color,brightness,0);
    }
    if(second%2){
      if(t<10){
        screen.draw_line(8,8,3,color,brightness);
        screen.draw_line(8,8,5,color,brightness);
        screen.draw_line(20,20,3,color,brightness);
        screen.draw_line(20,20,5,color,brightness);
      }else{
        screen.draw_line(9,9,3,color,brightness);
        screen.draw_line(9,9,5,color,brightness);
        screen.draw_line(21,21,3,color,brightness);
        screen.draw_line(21,21,5,color,brightness);
      }
    }
  }

  if(line){
    int passtime=hour*60+min;
    double t=passtime*1.0/1440.0;
    int pixels=floor((SCREEN_WIDTH-1)*t+0.5);
    screen.draw_line(0,pixels,0,color,brightness);
  }
  
  screen.show();
}

void Scene_clock::exist(){
#ifdef DEBUG
  Serial.printf("****exist scene: clock\n");
#endif
  key_close.off();
  key_back1.off();
  key_back2.off();
  key_back3.off();
}