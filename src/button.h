#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
  Button(int pin);
  void tick(unsigned long now);
  void register_shortPush(void (*func)());
  void register_longPush(void (*func)());
  void register_stopPush(void (*func)());
  static void empty_callback();

private:
  int pin;
  int push_count;
  void (*cb_shortPush)();
  void (*cb_longPush)();
  void (*cb_stopPush)();
  bool long_push;
  unsigned long last_time;
};

#endif  //BUTTON_H
