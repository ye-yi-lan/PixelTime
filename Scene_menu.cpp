#include<Arduino.h>
#include "Scene_menu.h"
#include "Scene_manager.h"

extern Hardware_key hardware_keys[4];

Scene_menu::Scene_menu(){
  key_left.set_key(&hardware_keys[1]);
  key_left.set_click_function([&](){
    pos--;
    if(pos<0)pos=7;
  });
  key_left.off();
  
  key_right.set_key(&hardware_keys[2]);
  key_right.set_click_function([&](){
    pos++;
    if(pos>7)pos=0;
  });
  key_right.off();
  
  key_enter.set_key(&hardware_keys[3]);
  key_enter.set_click_function([&](){
    Scene_manager::rt()->changer(static_cast<Scene_type>(pos));
  });
  key_enter.off();

  pos=0;
}

void Scene_menu::init(){

}

void Scene_menu::enter(){
#ifdef DEBUG
  Serial.printf("****enter scene: menu\n");
#endif
  key_left.on();
  key_right.on();
  key_enter.on();
}

void Scene_menu::update(){
#ifdef DEBUG
  // Serial.printf("=====scene:menu=====\n----update----\n");
  // Serial.printf("pos:%d\n",pos);
#endif
  key_left.update();
  key_right.update();
  key_enter.update();
}

void Scene_menu::draw(){
#ifdef DEBUG
  // Serial.printf("----draw----\n");
#endif
  v_screen.clear();
  int pl=pos-1,p=pos,pr=p+1;
  if(pl<0)pl=7;
  if(pl>7)pl=0;
  if(p<0)p=7;
  if(p>7)p=0;
  if(pr<0)pr=7;
  if(pr>7)pr=0;
  v_screen.draw_model(X[0],0,Model_type::icons,pl,App_theme::color,App_theme::brightness/3.0);
  v_screen.draw_model(X[1],0,Model_type::icons,p,App_theme::color,min(App_theme::brightness*2.0,1.0));
  v_screen.draw_model(X[2],0,Model_type::icons,pr,App_theme::color,App_theme::brightness/3.0);
  v_screen.draw_line(12,20,7,App_theme::color,App_theme::brightness/4.0);
  v_screen.show();
}

void Scene_menu::exist(){
#ifdef DEBUG
  Serial.printf("****exist scene: menu\n");
#endif
  key_left.off();
  key_right.off();
  key_enter.off();
}