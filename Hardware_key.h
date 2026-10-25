#ifndef _HARDWARE_KEY_H_
#define _HARDWARE_KEY_H_

enum class Key_event{
  none,click,hold
};

class Hardware_key{
  public:
    Hardware_key();
    void init(int id);
    void update();
    void debug();
    Key_event get_message();
  private:
    const int LONG_PRESS_MS=1000;
    const int DEBOUNCE_MS=20;
    int listen_pin;
    bool is_down;
    bool eve_click;
    bool is_hold;
    bool eve_hold;
    bool last_level;
    unsigned long change_time;
    unsigned long press_time;
};

#endif