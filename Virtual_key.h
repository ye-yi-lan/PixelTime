#ifndef _VIRTUAL_KEY_H_
#define _VIRTUAL_KEY_H_

#include"Hardware_key.h"
#include<functional>

class Virtual_key{
  public:
    void set_key(Hardware_key* k){
      key=k;
    }
    void set_click_function(std::function<void()> f){
      click=f;
    }
    void set_hold_function(std::function<void()> f){
      hold=f;
    }
    void set_none_function(std::function<void()> f){
      none=f;
    }
    void update(){
      if(!is)return;
      if(!key)return;
      switch(key->get_message()){
        case Key_event::none:
          if(none)none();
          break;
        case Key_event::click:
          if(click)click();
          break;
        case Key_event::hold:
          if(hold)hold();
          break;
      }
    }
    void on(){
      is=1;
    }
    void off(){
      is=0;
    }
  private:
    bool is=false;
    Hardware_key* key=nullptr;
    std::function<void()> click{};
    std::function<void()> hold{};
    std::function<void()> none{};
};

#endif