#include "Virtual_screen.h"
#include "tools.h"

extern Model_manager model_manager;
extern Screen screen;

Virtual_screen::Virtual_screen(int x,int y,int ms_everyframe){
  buf.resize(x*y,0x000000);
  ms_frame=ms_everyframe;
  hardware_screen=&screen;
  last_draw_time=0;
  this->x=x;
  this->y=y;
  if(x>SCREEN_WIDTH){
    need_scroll=1;
    last_scroll_x=0;
  }else{
    need_scroll=0;
  }
}

void Virtual_screen::debug(int mode){
  clear();
  CRGB color;
  int frame_max;
  if(mode==0){
    frame_max=SCREEN_NUM;
  }
  else if(mode==1){
    frame_max=SCREEN_HIGH;
  }
  else if(mode==2){
    frame_max=SCREEN_WIDTH;
  }
  else if(mode==3){
    frame_max=80;
  }
  else if(mode==4){
    frame_max=80;
  }

   if(debug_frame>=frame_max*7){
     debug_frame-=frame_max*7;
  }
  switch(debug_frame/frame_max){
    case 0:color=0xff0000;break;
    case 1:color=0x00ff00;break;
    case 2:color=0x0000ff;break;
    case 3:color=0xffff00;break;
    case 4:color=0xff00ff;break;
    case 5:color=0x00ffff;break;
    case 6:color=0xffffff;break;
  }

  if(mode==0){
    int this_led=debug_frame%SCREEN_NUM;
    int last_led= this_led==0 ? SCREEN_NUM-1 : this_led-1;
    buf[last_led]=0x000000;
    buf[this_led]=color;
#ifdef DEBUG
    Serial.printf("%d\n",debug_frame);
    Serial.printf("%d %d\n",this_led,color);
    Serial.printf("%d\n\n",last_led);
#endif
  }
  else if(mode==1){
    int this_line=debug_frame%SCREEN_HIGH;
    int last_line= this_line==0 ? SCREEN_HIGH-1 : this_line-1;
    for(int i=0;i<SCREEN_WIDTH;i++){
      buf[XY(i,this_line)]=color;
      buf[XY(i,last_line)]=0x000000;
    }
  }
  else if(mode==2){
    int this_line=debug_frame%SCREEN_WIDTH;
    int last_line= this_line==0 ? SCREEN_WIDTH-1 : this_line-1;
    for(int i=0;i<SCREEN_HIGH;i++){
      buf[XY(this_line,i)]=color;
      buf[XY(last_line,i)]=0x000000;
    }
  }
  else if(mode==3){
    int this_frame=debug_frame%frame_max;
    if(this_frame<40){
      draw_letter(0,0,'H',color);//,debug_frame/40.0);
      draw_letter(5,0,'E',color);//,debug_frame/40.0);
      draw_letter(10,0,'L',color);//,debug_frame/40.0);
      draw_letter(15,0,'L',color);//,debug_frame/40.0);
      draw_letter(20,0,'O',color);//,debug_frame/40.0);
    }else{
      draw_letter(0,0,'W',color);//,(debug_frame-40)/40.0);
      draw_letter(6,0,'O',color);//,(debug_frame-40)/40.0);
      draw_letter(12,0,'R',color);//,(debug_frame-40)/40.0);
      draw_letter(17,0,'L',color);//,(debug_frame-40)/40.0);
      draw_letter(22,0,'D',color);//,(debug_frame-40)/40.0);
    }
  }
  else if(mode==4){
    int this_frame=debug_frame%frame_max;
    if(this_frame<40){
      draw_model(0,0,Model_type::icons,0,color);
      draw_model(8,0,Model_type::icons,1,color);
      draw_model(16,0,Model_type::icons,2,color);
      draw_model(24,0,Model_type::icons,3,color);
    }else{
      draw_model(0,0,Model_type::icons,4,color);
      draw_model(8,0,Model_type::icons,5,color);
      draw_model(16,0,Model_type::icons,6,color);
      draw_model(24,0,Model_type::icons,7,color);
    }
  }
  debug_frame++;
}

void Virtual_screen::clear(){
  std::fill(buf.begin(),buf.end(),0x000000);
}

void Virtual_screen::draw_number(int x,int y,int number,CRGB color,float alpha,bool is_small,bool is_thin){
  if(number<0||number>=10)return;
  Model* l=model_manager.get_number(number,is_small,is_thin);
  draw_model(x,y,l,color,alpha);
}

void Virtual_screen::draw_letter(int x,int y,char letter,CRGB color,float alpha){
  Model* l=model_manager.get_letter(letter);
  draw_model(x,y,l,color,alpha);
}

void Virtual_screen::draw_loading(){
  draw_model(0,0,Model_type::others,0,0x00ffc8,App_theme::brightness/2.0);
}

void Virtual_screen::draw_model(int x,int y,Model* model,CRGB color,float alpha){
  CRGB out=change_brightness(color,alpha);
  for(int i=0;i<model->high;i++){
    for(int j=0;j<model->width;j++){
      if(model->data[j][i]){
        buf[XY(x+j,y+i)]=out;
      }
    }
  }
}
void Virtual_screen::draw_model(int x,int y,Model_type lx,int id,CRGB color,float alpha){
  Model* l=model_manager.get_model(lx,id);
  draw_model(x,y,l,color,alpha);
}
void Virtual_screen::draw_model(int x,int y,Model_type lx,Scene_type id,CRGB color,float alpha){
  draw_model(x,y,lx,static_cast<int>(id),color,alpha);
}


void Virtual_screen::draw_line(int x1,int x2,int y,CRGB color,float alpha){
  if(y<0||y>=this->y)return;
  CRGB out=change_brightness(color,alpha);
  for(int i=max(0,x1);i<=min(this->x,x2);i++){
    buf[XY(i,y)]=out;
  }
}

void Virtual_screen::draw_liney(int x,int y1,int y2,CRGB color,float alpha){
  if(x<0||x>=this->x)return;
  CRGB out=change_brightness(color,alpha);
  for(int i=max(0,y1);i<=min(this->y,y2);i++){
    buf[XY(x,i)]=out;
  }
}

int Virtual_screen::XY(int x,int y){
  if(x<0||x>=(this->x)||y<0||y>=(this->y)){
    return 0;
  }
  int ret;
  if(x%2==0){
    ret=SCREEN_HIGH*x+y;
  }
  else{
    ret=SCREEN_HIGH*(x+1)-y-1;
  }
  return ret;
}

void Virtual_screen::show(){
  hardware_screen->draw(*this);
  hardware_screen->show();
}