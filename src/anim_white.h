#ifndef ANIM_WHITE_H
#define ANIM_WHITE_H

#include "animation.h"

#define DIM_NUM 5

class White : public Animation
{
public:
  White(CRGB *leds, unsigned int count);
  void animate(unsigned long now);

private:
  unsigned long last_time;
  struct
  {
    uint8_t pos;
    uint8_t reduction;
    bool rising;
  } dim_pixels[DIM_NUM];
};

#endif // ANIM_WHITE_H
