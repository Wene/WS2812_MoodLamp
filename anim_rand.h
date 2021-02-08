#ifndef ANIM_RAND_H
#define ANIM_RAND_H

#include <FastLED.h>
#include "animation.h"

class Rand : public Animation
{
public:
  Rand(CRGB *leds, int count);
  void animate(unsigned long now);
private:
  CRGB *leds;
  int led_count;
  unsigned long step_time;
  unsigned long last_time;
};

#endif //ANIM_RAND_H
