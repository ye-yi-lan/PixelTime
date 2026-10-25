#include<Arduino.h>
#include "Scene_manager.h"
#include "Scene_menu.h"
#include "Scene_clock.h"

Scene* menu;
Scene* clock_scene;
Scene* calendar;
Scene* count_down;
Scene* timer;
Scene* weather;
Scene* game;
Scene* setting;
Scene* debug;

Scene_manager* Scene_manager::manager=nullptr;

Scene_manager* Scene_manager::rt(){
  if(!manager)manager=new Scene_manager();
  return manager;
}

Scene_manager::Scene_manager(){
  menu=new Scene_menu;
  clock_scene=new Scene_clock;
  //
  calendar=menu;
  count_down=menu;
  timer=menu;
  weather=menu;
  game=menu;
  setting=menu;
  debug=menu;

  now=menu;
  now_type=Scene_type::menu;
  now->enter();
}

void Scene_manager::init(){

}
void Scene_manager::update(){
#ifdef DEBUG
  // Serial.printf("now_scene:%d\n",(int)now_type);
#endif
  now->update();
}
void Scene_manager::draw(){
  now->draw();
}
void Scene_manager::changer(Scene_type type){
  now->exist();
#ifdef DEBUG
  Serial.printf("++++++++changing_scene...\n");
#endif
  now_type=type;
  switch(type){
    case Scene_type::menu : now=menu;break;
    case Scene_type::clock : now=clock_scene;break;
    case Scene_type::calendar : now=calendar;break;
    case Scene_type::count_down : now=count_down;break;
    case Scene_type::timer : now=timer;break;
    case Scene_type::weather : now=weather;break;
    case Scene_type::game : now=game;break;
    case Scene_type::setting : now=setting;break;
    case Scene_type::debug : now=debug;break;
  }
  now->enter();
}
Scene_manager::~Scene_manager(){
  delete menu;
  delete clock_scene;
  delete calendar;
  delete count_down;
  delete timer;
  delete weather;
  delete game;
  delete setting;
  delete debug;
}