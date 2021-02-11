#include "anim_lava.h"

Lava::Lava(CRGB *leds, int count)
{
  this->leds = leds;
  led_count = count;
  sub_pixels = 256 / count;
  dim_part = 200 / sub_pixels;
}

void Lava::animate(unsigned long now)
{
  if(now > last_hue_step + 350)
  {
    last_hue_step = now;
    hue_pos++;
  }
  
  if(now > last_bubble_step + 75)
  {
    last_bubble_step = now;
    for(uint8_t i = 0; i < led_count; i++)
    {
      leds[i].setHue(hue_pos);
    }
    uint8_t v_start = bubble_pos++; // position rolls automatically over
    for(uint8_t i = 0; i < 28; i++)
    {
      leds[(v_start++)/sub_pixels].subtractFromRGB(dim_part);
    }
  }
}
