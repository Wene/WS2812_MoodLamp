#ifndef ANIM_RAND_H
#define ANIM_RAND_H

#include "animation.h"

#define STEPS 20
#define SIDES 4
#define DOTS 5
#define SUB_COUNT STEPS*(DOTS-1)

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
  void new_dots();
  uint8_t sub_dots[SUB_COUNT];
};

#endif //ANIM_RAND_H
