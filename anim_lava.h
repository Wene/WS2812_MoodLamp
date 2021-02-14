#ifndef ANIM_LAVA_H
#define ANIM_LAVA_H

#include "animation.h"

class Lava : public Animation
{
public:
  Lava(CRGB *leds, unsigned int count);
  void animate(unsigned long now);
private:

  unsigned long last_hue_step;
  unsigned long last_bubble_step;
  uint8_t hue_pos;
  unsigned int bubble_pos;
  
  uint8_t sub_pixels;
  uint8_t dim_part;
};


#endif //ANIM_LAVA_H
