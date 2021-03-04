#include "anim_lava.h"

Lava::Lava(CRGB *leds, unsigned int count) : Animation(leds, count)
{
  dim_part = 200 / SUB_POSITIONS;
  ledsPerSide = led_count / SIDES;
  hue_pos = 0;
  cyclePos = 0;

  subStep = (SUB_PIX_COUNT - SUB_POSITIONS) / ledsPerSide;

  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    for(uint8_t iBubble = BUBBLES-1; iBubble > 0; iBubble--)
    {
      bubbles[iSide][iBubble] = false;
    }
  }
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

    uint8_t subPixelPos[ledsPerSide];
    uint8_t iSubPos = SUB_PIX_COUNT - 1 - cyclePos;
    for(int8_t i = ledsPerSide-1; i >= 0; i--)
    {
      subPixelPos[i] = iSubPos;
      iSubPos -= subStep;
    }

    for(uint8_t iSide = 0; iSide < SIDES; iSide++)
    {
      for(uint8_t iPos = 0; iPos < ledsPerSide; iPos++)
      {
        uint8_t iLED = iSide * ledsPerSide + iPos;
        CRGB &workingLED = leds[iLED];
        workingLED.setHue(hue_pos);

        uint8_t iPart = subPixelPos[iPos] / SUB_POSITIONS;
        uint8_t subPos = subPixelPos[iPos] % SUB_POSITIONS;
        bool start = bubbles[iSide][iPart];
        bool end = bubbles[iSide][iPart+1];

        if(start || end)
        {
          unsigned int startValue = start ? 200 : 0;
          unsigned int endValue = end ? 200 : 0;
          unsigned int diff = subPos * endValue + (SUB_POSITIONS - subPos) * startValue;
          diff /= SUB_POSITIONS;
          workingLED.subtractFromRGB(diff);
        }
      }
    }

    cyclePos++;
    if(cyclePos >= SUB_POSITIONS)
    {
      cyclePos = 0;
      bubble_move();
    }
  }
}

void Lava::bubble_move()
{
  for(uint8_t iSide = 0; iSide < SIDES; iSide++)
  {
    for(uint8_t iBubble = BUBBLES-1; iBubble > 0; iBubble--)
    {
      bubbles[iSide][iBubble] = bubbles[iSide][iBubble-1];
    }
    bool active = (5 == random(0, 10));
    bubbles[iSide][0] = active;
  }
}
