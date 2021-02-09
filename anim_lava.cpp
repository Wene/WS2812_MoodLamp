#include "anim_lava.h"

Lava::Lava(CRGB *leds, int count)
{
  this->leds = leds;
  led_count = count;
}

void Lava::animate(unsigned long now)
{
  if(now > last_hue_step + 50)
  {
    last_hue_step = now;
    hue_pos++;
  }
  for(int i = 0; i < led_count; i++)
  {
    leds[i].setHue(hue_pos);
  }
}
