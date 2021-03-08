#ifndef ANIMATION_H
#define ANIMATION_H

#include <FastLED.h>

class Animation
{
protected:
  CRGB *leds;
  unsigned int led_count;
public:
  Animation(CRGB *leds, unsigned int led_count);
  virtual void animate(unsigned long) = 0;
  virtual ~Animation();
};


#endif //ANIMATION_H
