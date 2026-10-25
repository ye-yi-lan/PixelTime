#ifndef _SCENE_H_
#define _SCENE_H_

enum class Scene_type{
  clock,calendar,count_down,timer,weather,game,setting,debug,menu
};

class Scene{
  public:
    virtual void init()=0;
    virtual void enter()=0;
    virtual void update()=0;
    virtual void draw()=0;
    virtual void exist()=0;
};

/*
#include"Scene.h"

class Scene_menu : public Scene{
  public: 
    Scene_menu();
    void init();
    void enter();
    void update();
    void draw();
    void exist();
  private:
    
};


#include<Arduino.h>
#include "Scene_menu.h"
#include "Scene_manager.h"

extern Hardware_key hardware_keys[4];

Scene_menu::Scene_menu(){
  
}

void Scene_menu::init(){
#ifdef DEBUG
  Serial.printf("****init scene: menu\n");
#endif
}

void Scene_menu::enter(){
#ifdef DEBUG
  Serial.printf("****enter scene: menu\n");
#endif

}

void Scene_menu::update(){
#ifdef DEBUG
  Serial.printf("=====scene:menu=====\n----update----\n");
#endif

}

void Scene_menu::draw(){
#ifdef DEBUG
  Serial.printf("----draw----\n");
#endif

}

void Scene_menu::exist(){
#ifdef DEBUG
  Serial.printf("****exist scene: menu\n");
#endif

}
*/

#endif