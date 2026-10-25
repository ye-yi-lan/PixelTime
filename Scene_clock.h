#ifndef _SCENE_CLOCK_H_
#define _SCENE_CLOCK_H_

#include"Scene.h"
#include"Virtual_screen.h"
#include"Virtual_key.h"

class Scene_clock : public Scene{
  public: 
    Scene_clock();
    void init();
    void enter();
    void update();
    void draw();
    void exist();
  private:
    bool is_setting=0;
    bool show_second=1;//0-hh:mm 1-hh:mm:ss
    bool show_24h=1;
    bool show_smallsize=1;
    float brightness=1.0;
    float brightness_buf=1.0;
    float brightness_usr=1.0;
    bool line=1;
    bool auto_color=1;
    int hour;
    int min;
    int second;
    int show_mode=0;
    CRGB color=0x000000;
    CRGB color_buf;
    Virtual_screen screen;
    Virtual_key key_close;
    Virtual_key key_back1,key_back2,key_back3;

    const CHSV colors[24] = {
      CHSV(172, 255, 255),  // 0时
      CHSV(172, 255, 255),  // 1时
      CHSV(171, 253, 255),  // 2时
      CHSV(170, 250, 255),  // 3时
      CHSV(168, 240, 255),  // 4时
      CHSV(162, 220, 255),  // 5时
      CHSV(156, 180, 255),  // 6时
      CHSV(152, 140, 255),  // 7时
      CHSV(148, 110, 255),  // 8时
      CHSV(145, 80,  255),  // 9时
      CHSV(142, 45,  255),  // 10时
      CHSV(140, 15,  255),  // 11时
      CHSV(140, 0,   255),  // 12时
      CHSV(50,  15,  255),  // 13时
      CHSV(45,  40,  255),  // 14时
      CHSV(40,  80,  255),  // 15时
      CHSV(35,  120, 255),  // 16时
      CHSV(25,  170, 255),  // 17时
      CHSV(10,  220, 255),  // 18时
      CHSV(250, 240, 255),  // 19时
      CHSV(235, 245, 255),  // 20时
      CHSV(220, 250, 255),  // 21时
      CHSV(200, 252, 255),  // 22时
      CHSV(185, 255, 255),  // 23时
    };
    const float brightnesses[24] = {
      0.39f,  // 0时
      0.39f,  // 1时
      0.39f,  // 2时
      0.39f,  // 3时
      0.42f,  // 4时
      0.50f,  // 5时
      0.60f,  // 6时
      0.72f,  // 7时
      0.83f,  // 8时
      0.90f,  // 9时
      0.90f,  // 10时
      0.90f,  // 11时
      0.92f,  // 12时
      0.90f,  // 13时
      0.90f,  // 14时
      0.90f,  // 15时
      0.85f,  // 16时
      0.90f,  // 17时
      0.92f,  // 18时
      0.90f,  // 19时
      0.85f,  // 20时
      0.79f,  // 21时
      0.68f,  // 22时
      0.55f,  // 23时
    };
};

#endif