#include "anim_rand.h"

Rand::Rand(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  step_time = 30;
  cycle_pos = 0;

  for(uint8_t iDot = 0; iDot < DOTS; iDot++)
  {
    new_dots();
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
      CRGB pix;
      pix.setHue(sides[iSide][iPart]);
      uint8_t rStart = pix.r;
      pix.setHue(sides[iSide][iPart+1]);
      uint8_t rEnd = pix.r;
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
      CRGB pix;
      pix.setHue(sides[iSide][iPart]);
      uint8_t gStart = pix.g;
      pix.setHue(sides[iSide][iPart+1]);
      uint8_t gEnd = pix.g;
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
      CRGB pix;
      pix.setHue(sides[iSide][iPart]);
      uint8_t bStart = pix.b;
      pix.setHue(sides[iSide][iPart+1]);
      uint8_t bEnd = pix.b;
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
    new_dots();
  }
}

void Rand::new_dots()
{
  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    for(uint8_t iDot = DOTS - 1; iDot > 0; iDot--)
    {
      sides[iSide][iDot] = sides[iSide][iDot-1];
    }
    sides[iSide][0] = random(0, 256);
  }
}
