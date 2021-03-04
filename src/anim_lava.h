#ifndef ANIM_LAVA_H
#define ANIM_LAVA_H

#include "animation.h"

#define SIDES 4
#define BUBBLES 5
#define SUB_POSITIONS 20
#define SUB_PIX_COUNT SUB_POSITIONS*(BUBBLES-1)

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
  
  bool bubbles[SIDES][BUBBLES];
  uint8_t ledsPerSide;
  uint8_t dim_part;
  uint8_t cyclePos;
  uint8_t subStep;

  void bubble_move();
};


#endif //ANIM_LAVA_H
