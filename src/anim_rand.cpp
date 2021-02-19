#include "anim_rand.h"

Rand::Rand(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  step_time = 30;
  cycle_pos = 0;
  
  for(uint8_t i = 0; i < SIDES; i++)
  {
    for(uint8_t j = 0; j < DOTS; j++)
    {
      new_dot(&sides[i]);
    }
  }
}

void Rand::animate(unsigned long now)
{
  if(now < last_time + step_time)
  {
    return;
  }
  last_time = now;

  int8_t subStep = (SUB_COUNT - STEPS) / (led_count / SIDES);
  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    int8_t sideFirst = iSide * (led_count / SIDES);
    int8_t sideLast = (sideFirst + led_count / SIDES) - 1;
    
    uint8_t iSubDot = 0;
    for(uint8_t iPart = 0; iPart < DOTS-1; iPart++)
    {
      uint8_t rStart = sides[iSide].dots[iPart].r;
      uint8_t rEnd = sides[iSide].dots[iPart+1].r;
      for(uint8_t iStep = 0; iStep < STEPS; iStep++)
      {
        unsigned int sum = rEnd * iStep + rStart * (STEPS-iStep);
        sub_dots[iSubDot++] = sum / STEPS;
      }
    }
    // sub_dots should now have all red pixels in it...
    uint8_t iPos = SUB_COUNT - 1 - cycle_pos;
    for(int8_t iLed = sideLast; iLed >= sideFirst; iLed--)
    {
      leds[iLed].r = sub_dots[iPos];
      iPos -= subStep;
    }
    
    iSubDot = 0;
    for(uint8_t iPart = 0; iPart < DOTS-1; iPart++)
    {
      uint8_t gStart = sides[iSide].dots[iPart].g;
      uint8_t gEnd = sides[iSide].dots[iPart+1].g;
      for(uint8_t iStep = 0; iStep < STEPS; iStep++)
      {
        unsigned int sum = gEnd * iStep + gStart * (STEPS-iStep);
        sub_dots[iSubDot++] = sum / STEPS;
      }
    }
    // sub_dots should now have all green pixels in it...
    iPos = SUB_COUNT - 1 - cycle_pos;
    for(int8_t iLed = sideLast; iLed >= sideFirst; iLed--)
    {
      leds[iLed].g = sub_dots[iPos];
      iPos -= subStep;
    }
    
    iSubDot = 0;
    for(uint8_t iPart = 0; iPart < DOTS-1; iPart++)
    {
      uint8_t bStart = sides[iSide].dots[iPart].b;
      uint8_t bEnd = sides[iSide].dots[iPart+1].b;
      for(uint8_t iStep = 0; iStep < STEPS; iStep++)
      {
        unsigned int sum = bEnd * iStep + bStart * (STEPS-iStep);
        sub_dots[iSubDot++] = sum / STEPS;
      }
    }
    // sub_dots should now have all blue pixels in it...
    iPos = SUB_COUNT - 1 - cycle_pos;
    for(int8_t iLed = sideLast; iLed >= sideFirst; iLed--)
    {
      leds[iLed].b = sub_dots[iPos];
      iPos -= subStep;
    }
  }
  
  cycle_pos++;
  if(cycle_pos >= STEPS)
  {
    cycle_pos = 0;
    for(uint8_t i = 0; i < SIDES; i++)
    {
      new_dot(&sides[i]);
    }
  }
}

void Rand::new_dot(Side *my_side)
{
  for(uint8_t i = DOTS - 1; i > 0; i--)
  {
    my_side->dots[i] = my_side->dots[i-1];
  }
  CRGB new_pixel;
  new_pixel.setHue(random(0, 256));
  my_side->dots[0] = {.r = new_pixel.r, .g = new_pixel.g, .b = new_pixel.b};
}
