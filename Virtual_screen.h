#ifndef _VIRTUAL_SCREEN_H_
#define _VIRTUAL_SCREEN_H_

#include "Screen.h"
#include <vector>
#include"config.h"
#include"Model_manager.h"

class Virtual_screen{
  friend class Screen;
  public:
    Virtual_screen(int x=SCREEN_WIDTH,int y=SCREEN_HIGH,int ms_everyframe=500);
    
    void debug(int mode);
    void clear();
    void draw_number(int x,int y,int number,CRGB color=0xffffff,float alpha=1.0,bool is_small=1,bool is_thin=0);
    void draw_letter(int x,int y,char letter,CRGB color=0xffffff,float alpha=1.0);
    void draw_loading();
    void draw_model(int x,int y,Model* model,CRGB color=0xffffff,float alpha=1.0);
    void draw_model(int x,int y,Model_type lx,int id,CRGB color=0xffffff,float alpha=1.0);
    void draw_model(int x,int y,Model_type lx,Scene_type id,CRGB color=0xffffff,float alpha=1.0);
    void draw_line(int x1,int x2,int y,CRGB color=0xffffff,float alpha=1.0);
    void draw_liney(int x,int y1,int y2,CRGB color=0xffffff,float alpha=1.0);
    void show();
  protected:
    std::vector<CRGB> buf;
    int x,y;
    int ms_frame;
    unsigned long last_draw_time;
    bool need_scroll;
    int last_scroll_x;
    Screen* hardware_screen;
  private:
    int XY(int x,int y);
    int debug_frame=0;
};

#endif