#ifndef ANIM_RAND_H
#define ANIM_RAND_H

#include "animation.h"

#define STEPS 20
#define SIDES 4
#define DOTS 5
#define SUB_PIXELS_COUNT STEPS*(DOTS-1)

class Rand : public Animation
{
public:
  Rand(CRGB *leds, unsigned int count);
  void animate(unsigned long now);
  
private:
  unsigned long step_time;
  unsigned long last_time;
  
  uint8_t sides[SIDES][DOTS];
  uint8_t cycle_pos;
  uint8_t subStep;
  uint8_t ledsPerSide;

  void new_dots();
};

#endif //ANIM_RAND_H
