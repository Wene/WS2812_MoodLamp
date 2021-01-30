#include "anim_lava.h"

namespace animation
{

Lava::Lava(CRGB *leds, int count)
{
  this->leds = leds;
  led_count = count;
  pos = 0;
  step_time = 100;
  
  color[0] = CRGB::Red;
  color[1] = CRGB::Green;
  color[2] = CRGB::Blue;
  act_col = 0;
}

Lava::animate(unsigned long now)
{
  if(now < last_time + step_time)
  {
    return;
  }
  last_time = now;

  leds[pos] = color[act_col];
  FastLED.show();
  
  pos++;
  if(pos >= led_count)
  {
    pos = 0;
    act_col++;
    if(act_col > 2)
    {
      act_col = 0;
    }
  }
}

} //namespace
