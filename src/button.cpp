#include "button.h"
#include "Arduino.h"

#define SHORT 50
#define LONG_START 300
#define INTERVAL 100

Button::Button(int pin) : pin{pin}
{
  pinMode(pin, INPUT_PULLUP);
  push_count = 0;

  cb_shortPush = empty_callback;  
  cb_longPush = empty_callback;  
  cb_stopPush = empty_callback;
}

void Button::tick(unsigned long now)
{
  bool pushed = !digitalRead(pin);  
  if(pushed)
  {
    if(!long_push)
    {
      push_count++;
      if(now >= last_time + LONG_START)
      {
        long_push = true;
        last_time = now;
        cb_longPush();
      }
    }
    else // long_push == true
    {
      if(now >= last_time + INTERVAL)
      {
        last_time = now;
        cb_longPush();
      }
    }
  }
  else  // not pushed
  {
    if(push_count && !long_push && now >= last_time + SHORT)
    {
      cb_shortPush();
    }
    else if(long_push)
    {
      long_push = false;
      cb_stopPush();
    }
    push_count = 0;
    last_time = now;
  }
}

void Button::register_shortPush(void (*func)())
{
  cb_shortPush = func;
}

void Button::register_longPush(void (*func)())
{
  cb_longPush = func;
}

void Button::register_stopPush(void (*func)())
{
  cb_stopPush = func;
}

void Button::empty_callback(){}
