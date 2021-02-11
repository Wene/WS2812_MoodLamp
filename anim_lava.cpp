#include "anim_lava.h"

Lava::Lava(CRGB *leds, int count)
{
  this->leds = leds;
  led_count = count;
  sub_pixels = 20;
  dim_part = 200 / sub_pixels;
}

void Lava::animate(unsigned long now)
{
  if(now > last_hue_step + 350)
  {
    last_hue_step = now;
    hue_pos++;
  }
  
  if(now > last_bubble_step + 30)
  {
    last_bubble_step = now;
    for(uint8_t i = 0; i < led_count; i++)
    {
      leds[i].setHue(hue_pos);
    }
    
    unsigned int v_start = bubble_pos;
    bubble_pos++;
    if(bubble_pos >= sub_pixels * led_count)
    {
      bubble_pos = 0;
    }

    for(uint8_t i = 0; i < 28; i++)
    {
      unsigned int pos = v_start / sub_pixels;
      v_start++;
      if(pos >= led_count)
      {
        pos -= led_count;
      }
      leds[pos].subtractFromRGB(dim_part);
    }
  }
}
