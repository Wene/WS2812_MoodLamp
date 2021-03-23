#include "anim_white.h"

White::White(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  for(uint8_t i = 0; i < DIM_NUM; i++)
  {
    dim_pixels[i].pos = random(led_count);
    dim_pixels[i].reduction = random(100, 200);
    dim_pixels[i].rising = (random(2) == 1);
  }
  last_time = 0;
}

void White::animate(unsigned long now)
{
  if(now < last_time + 30)
  {
    return;
  }
  last_time = now;

  for(uint8_t iLed = 0; iLed < led_count; iLed++)
  {
    leds[iLed] = 0xa0b075;
    for(uint8_t i = 0; i < DIM_NUM; i++)
    {
      if(dim_pixels[i].pos == iLed)
      {
        if(dim_pixels[i].rising)
        {
          dim_pixels[i].reduction += 10;
          if(dim_pixels[i].reduction >= 200)
          {
            dim_pixels[i].rising = false;
          }
        }
        else  // falling
        {
          dim_pixels[i].reduction -= 10;
        }
        leds[iLed].subtractFromRGB(dim_pixels[i].reduction);

        if(dim_pixels[i].reduction <= 10)
        {
          dim_pixels[i].rising = true;
          dim_pixels[i].pos = random(led_count);
        }
        break;  // corresponding LED found - search no further.
      }
    }
  }
}

