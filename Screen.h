#ifndef _SCREEN_H_
#define _SCREEN_H_

#include<Arduino.h>
#include<FastLED.h>

class Virtual_screen;

class Screen{
  public:
    void input();
    void clear();
    void draw(Virtual_screen &screen);
    void show();
    void update(int interval);
  private:
    unsigned long timer;
};

#endif
