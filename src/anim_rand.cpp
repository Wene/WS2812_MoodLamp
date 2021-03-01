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

  uint8_t ledsPerSide = led_count / SIDES;
  uint8_t subStep = (SUB_COUNT - STEPS) / ledsPerSide;
  uint8_t positionsToCalculate[ledsPerSide];

  uint8_t iPos = SUB_COUNT - 1 - cycle_pos;
  for(int8_t iLed = ledsPerSide-1; iLed >= 0; iLed--)
  {
    positionsToCalculate[iLed] = iPos;
    iPos -= subStep;
  }

  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    uint8_t sideStart = iSide * ledsPerSide;
    
    for(uint8_t iPos = 0; iPos < ledsPerSide; iPos++)
    {
      uint8_t iLed = sideStart + iPos;
      uint8_t iPart = positionsToCalculate[iLed] / STEPS;
      uint8_t subPos = positionsToCalculate[iLed] % STEPS;

      CRGB startPix;
      startPix.setHue(sides[iSide][iPart]);
      CRGB endPix;
      endPix.setHue(sides[iSide][iPart+1]);

      unsigned int red = subPos * endPix.r + (STEPS - subPos) * startPix.r;
      unsigned int green = subPos * endPix.g + (STEPS - subPos) * startPix.g;
      unsigned int blue = subPos * endPix.b + (STEPS - subPos) * startPix.b;
      leds[iLed].r = red / STEPS;
      leds[iLed].g = green / STEPS;
      leds[iLed].b = blue / STEPS;
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
