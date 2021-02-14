#include "anim_rand.h"

Rand::Rand(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  step_time = 200;
}

void Rand::animate(unsigned long now)
{
  if(now < last_time + step_time)
  {
    return;
  }
  last_time = now;

  int side_count = led_count / 4;
  for(int side = 0; side < 4; side++)
  {
    int side_min = side * side_count;
    for(int led = side_min + (side_count-1); led > side_min; led--)
    {
      leds[led] = leds[led-1];
    }
    leds[side_min].setHue(random(0, 246));
  }
}
