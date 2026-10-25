#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "Hardware_key.h"
#include<Arduino.h>
#include"config.h"

Hardware_key::Hardware_key(){
  is_down=0;
  is_hold=0;
  last_level=1;
  change_time=0;
  press_time=0;
}

void Hardware_key::init(int id){
  switch(id){
    case 0:listen_pin=BUTTON0_PIN;break;
    case 1:listen_pin=BUTTON1_PIN;break;
    case 2:listen_pin=BUTTON2_PIN;break;
    case 3:listen_pin=BUTTON3_PIN;break;
  }
  pinMode(listen_pin,INPUT_PULLUP);
}

void Hardware_key::update(){
  eve_click=0;
  eve_hold=0;
  bool now_level=digitalRead(listen_pin);
  unsigned long now_time=millis();
  if(now_level!=last_level){
    if(change_time==0){
      change_time=now_time;
    }
    if(now_time-change_time>=DEBOUNCE_MS){
      change_time=0;
      is_down=!now_level;
      last_level=now_level;
      if(is_down){
        press_time=now_time;
      }else{
        if((now_time-press_time)<LONG_PRESS_MS){
          eve_click=1;
        }
        press_time=0;
      }
    }
  }else{
    if(now_time-change_time>=DEBOUNCE_MS){
      change_time=0;
    }
  }
  if(is_down&&press_time!=0&&(now_time-press_time)>=LONG_PRESS_MS){
    is_hold=1;
    eve_hold=1;
  }else{
    is_hold=0;
  }
}

void Hardware_key::debug(){
  if(eve_click){
    Serial.printf("click\n");
    return;
  }
  if(eve_hold){
    Serial.printf("hold\n");
    return;
  }
  Serial.printf("up\n");
}

Key_event Hardware_key::get_message(){
  if(eve_click){
    return Key_event::click;
  }
  if(eve_hold){
    return Key_event::hold;
  }
  return Key_event::none;
}