#ifndef _MODEL_H
#define _MODEL_H_

#include "config.h"
#include <initializer_list>

class Virtual_screen;

class Model{
  friend class Virtual_screen;
  public:
    Model(){
      for(int i=0;i<SCREEN_WIDTH;i++){
        for(int j=0;j<SCREEN_HIGH;j++){
          data[i][j]=0;
        }
      }
    }
    void init(short int x,short int y){
      width=x;
      high=y;
    }
    void set(short int y,std::initializer_list<bool> d){
      int x=0;
      if(y>=high)return;
      for(bool dot:d){
        if(x>=width)break;
        data[x][y]=dot;
        x++;
      }
    }
  protected:
    bool data[SCREEN_WIDTH][SCREEN_HIGH];
    short int high;
    short int width;
};

#endif