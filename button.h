#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
  Button(int pin);
  tick(unsigned long now);
  register_shortPush(void (*func)());
  register_longPush(void (*func)());

private:
  int pin;
  int push_count;
  (*cb_shortPush)();
  (*cb_longPush)();
  bool long_push;
  unsigned long last_time;
};

#endif  //BUTTON_H
