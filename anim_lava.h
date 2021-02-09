#ifndef ANIM_LAVA_H
#define ANIM_LAVA_H

#include <FastLED.h>
#include "animation.h"

class Lava : public Animation
{
public:
  Lava(CRGB *leds, int count);
  void animate(unsigned long now);
private:
  CRGB *leds;
  int led_count;

  unsigned long last_hue_step;
  uint8_t hue_pos;
  
};


#endif //ANIM_LAVA_H
