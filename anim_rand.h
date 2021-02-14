#ifndef ANIM_RAND_H
#define ANIM_RAND_H

#include "animation.h"

class Rand : public Animation
{
public:
  Rand(CRGB *leds, unsigned int count);
  void animate(unsigned long now);
private:
  unsigned long step_time;
  unsigned long last_time;
};

#endif //ANIM_RAND_H
