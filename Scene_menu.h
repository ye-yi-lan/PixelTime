#ifndef _SCENE_MENU_H_
#define _SCENE_MENU_H_

#include"Scene.h"
#include"Virtual_screen.h"
#include"Virtual_key.h"

class Scene_menu : public Scene{
  public: 
    Scene_menu();
    void init();
    void enter();
    void update();
    void draw();
    void exist();
  private:
    int pos=0;
    Virtual_screen v_screen;
    Virtual_key key_left;
    Virtual_key key_right;
    Virtual_key key_enter;
    const int X[3]={3,13,23};
};

#endif