#ifndef ANIM_RAND_H
#define ANIM_RAND_H

#include "FastLED.h"

namespace animation
{

class Rand
{
public:
  Rand(CRGB *leds, int count);
  animate(unsigned long now);
private:
  CRGB *leds;
  int led_count;
  unsigned long step_time;
  unsigned long last_time;
};

} //namespace

#endif //ANIM_RAND_H
