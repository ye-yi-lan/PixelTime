#include"Screen.h"
#include"Model_manager.h"
#include "Virtual_screen.h"

extern CRGB leds[SCREEN_NUM];

void Screen::input(){
  FastLED.addLeds<WS2812B,SCREEN_PIN,GRB>(leds,SCREEN_NUM).setCorrection(TypicalLEDStrip);
  FastLED.setDither(BINARY_DITHER);
  // FastLED.setBrightness(128);
  timer=0;
}

void Screen::clear(){
  fill_solid(leds,SCREEN_NUM,0x000000);
}

void Screen::draw(Virtual_screen &screen){
  if(screen.need_scroll){
    if(timer-screen.last_draw_time>=screen.ms_frame){
      screen.last_draw_time=timer;
      screen.last_scroll_x+=2;
      if(screen.last_scroll_x>screen.x){
        screen.last_scroll_x=-32;
      }
    }
    std::copy(screen.buf.begin()+max(screen.last_scroll_x,0)*SCREEN_HIGH,
              screen.buf.begin()+max(screen.last_scroll_x,0)*SCREEN_HIGH + min(min(SCREEN_WIDTH,SCREEN_WIDTH+screen.last_scroll_x),screen.x-screen.last_scroll_x)*SCREEN_HIGH
              ,leds+max(0-screen.last_scroll_x*SCREEN_HIGH,0));
  }else{
    std::copy(screen.buf.begin(),screen.buf.end(),leds);
  }
}

void Screen::show(){
  FastLED.show();
}

void Screen::update(int interval){
  timer+=interval;
}