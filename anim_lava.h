#ifndef ANIM_LAVA_H
#define ANIM_LAVA_H

#include "FastLED.h"

namespace animation
{

class Lava
{
public:
  Lava(CRGB *leds, int count);
  animate(unsigned long now);
private:
  CRGB *leds;
  int led_count;
  unsigned int pos;
  int step_time;
  unsigned long last_time;
  CRGB color[3];
  int act_col;
};

} //namespace

#endif //ANIM_LAVA_H
