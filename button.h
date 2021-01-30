#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
  Button(int pin);
  tick(unsigned long now);
  register_shortPush(void (*func)());
  register_longPush(void (*func)());
  register_stopPush(void (*func)());

private:
  static void empty_callback();
  int pin;
  int push_count;
  (*cb_shortPush)();
  (*cb_longPush)();
  (*cb_stopPush)();
  bool long_push;
  unsigned long last_time;
};

#endif  //BUTTON_H
