#ifndef _TOOLS_H_
#define _TOOLS_H_

#include<FastLED.h>

const uint8_t gamma_table[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,
3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,
6,7,7,7,8,8,8,9,9,9,10,10,11,11,11,12,
12,13,13,13,14,14,15,15,16,16,17,17,18,18,19,19,
20,20,21,22,22,23,23,24,25,25,26,26,27,28,28,29,
30,30,31,32,33,33,34,35,35,36,37,38,39,39,40,41,
42,43,43,44,45,46,47,48,49,49,50,51,52,53,54,55,
56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,
73,74,75,76,77,78,79,81,82,83,84,85,87,88,89,90,
91,93,94,95,97,98,99,100,102,103,105,106,107,109,110,111,
113,114,116,117,119,120,121,123,124,126,127,129,130,132,133,135,
137,138,140,141,143,145,146,148,149,151,153,154,156,158,159,161,
163,165,166,168,170,172,173,175,177,179,181,182,184,186,188,190,
192,194,196,197,199,201,203,205,207,209,211,213,215,217,219,221,
223,225,227,229,231,234,236,238,240,242,244,246,248,251,253,255
};

inline CRGB mix_color(CRGB c1,float a1,CRGB c2,float a2){
  int r=c1.r*a1+c2.r*a2;
  int g=c1.g*a1+c2.g*a2;
  int b=c1.b*a1+c2.b*a2;
  r=min(255,max(0,r));
  g=min(255,max(0,g));
  b=min(255,max(0,b));
  return CRGB(r,g,b);
}

inline CHSV mix_color(CHSV c1,float a1,CHSV c2,float a2){
  int d=(int)c2.h-(int)c1.h;
  if(d>127)d-=256;
  if(d<-127)d+=256;
  int h=c1.h+d*a2;
  int s=c1.s*a1+c2.s*a2;
  int v=c1.v*a1+c2.v*a2;
  h=min(255,max(0,h));
  s=min(255,max(0,s));
  v=min(255,max(0,v));
  return CHSV(h,s,v);
}

inline int get_alpha(float a){
  int t=floor(a*(188-16)+0.5)+16; //gamma_table[188]=MAX_BRIGHTNESS,gamma_table[16]=MIN_BRIGHTNESS
  return max(min(gamma_table[t],MAX_BRIGHTNESS),MIN_BRIGHTNESS);
}

inline uint8_t scale_round(uint8_t v, uint8_t scale){
  uint16_t t = (uint16_t)v * scale + 128;
  return t >> 8;
}

inline CRGB change_brightness(CRGB c,float a){
  uint8_t scale = constrain(get_alpha(a), 0, MAX_BRIGHTNESS);
  CRGB out;
  out.r=scale_round(c.r,scale);
  out.g=scale_round(c.g,scale);
  out.b=scale_round(c.b,scale);
  return out;
}

#endif