#include "anim_rand.h"

Rand::Rand(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  step_time = 30;
  cycle_pos = 0;

  ledsPerSide = led_count / SIDES;
  subStep = (SUB_PIXELS_COUNT - STEPS) / ledsPerSide;

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

  uint8_t subPixelPos[ledsPerSide];
  uint8_t iSubPos = SUB_PIXELS_COUNT - 1 - cycle_pos;
  for(int8_t i = ledsPerSide-1; i >= 0; i--)
  {
    subPixelPos[i] = iSubPos;
    iSubPos -= subStep;
  }

  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    uint8_t sideStart = iSide * ledsPerSide;
    
    for(uint8_t iPos = 0; iPos < ledsPerSide; iPos++)
    {
      uint8_t iLed = sideStart + iPos;
      uint8_t iPart = subPixelPos[iPos] / STEPS;
      uint8_t subPos = subPixelPos[iPos] % STEPS;

      CRGB startPix;
      startPix.setHue(sides[iSide][iPart]);
      CRGB endPix;
      endPix.setHue(sides[iSide][iPart+1]);

      unsigned int red = subPos * endPix.red + (STEPS - subPos) * startPix.red;
      unsigned int green = subPos * endPix.green + (STEPS - subPos) * startPix.green;
      unsigned int blue = subPos * endPix.blue + (STEPS - subPos) * startPix.blue;
      leds[iLed].red = red / STEPS;
      leds[iLed].green = green / STEPS;
      leds[iLed].blue = blue / STEPS;
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
