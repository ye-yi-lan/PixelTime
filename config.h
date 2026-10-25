#ifndef _CONFIG_H_
#define _CONFIG_H_

#define BUTTON0_PIN 0
#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3

#define SCREEN_PIN 21

#define LED_PIN 5

#define SCREEN_HIGH 8
#define SCREEN_WIDTH 32
#define SCREEN_NUM (SCREEN_HIGH*SCREEN_WIDTH)

#define FPS 10

#define DEBUG

#define MAX_BRIGHTNESS 128
#define MIN_BRIGHTNESS 1

namespace App_theme{
  inline int color=0xc9dd22;
  inline float brightness=0.5;
}

#endif