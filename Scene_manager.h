#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Scene.h"

class Scene_manager{
  public:
    static Scene_manager* rt();
    void init();
    void update();
    void draw();
    void changer(Scene_type type);
    ~Scene_manager();
  private:
    static Scene_manager* manager;
    Scene_manager();

    Scene* now;
    Scene_type now_type;
};

#endif