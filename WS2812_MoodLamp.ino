#include "FastLED.h"
#include "button.h"
#include "animation.h"
#include "anim_rand.h"
#include "anim_lava.h"

#define NUM_LEDS 32
#define DATA_PIN 10
#define BUTTON_PIN 9

CRGB leds[NUM_LEDS];

Button btn(BUTTON_PIN);
Rand anim_rand(leds, NUM_LEDS);
Lava anim_lava(leds, NUM_LEDS);

void dim();
void turnDim();
void cycleAnim();

bool light_on = false;
void toggleLight()
{
  light_on = !light_on;
  if(light_on)
  {
    btn.register_longPush(dim);
    btn.register_stopPush(turnDim);    
  }
  else
  {
    FastLED.clear();
    FastLED.show();
    btn.register_longPush(Button::empty_callback);
    btn.register_stopPush(cycleAnim);
  }
}

bool dim_up = true;
void turnDim()
{
  dim_up = !dim_up;
}

uint8_t brightness = 30;
void dim()
{
  if(dim_up && brightness < 255)
  {
    brightness++;
  }
  else if(!dim_up && brightness > 0)
  {
    brightness--;
  }
  FastLED.setBrightness(brightness);
}

Animation *anim;
void cycleAnim()
{
  if(anim == &anim_rand)
  {
    anim = &anim_lava;
  }
  else
  {
    anim = &anim_rand;
  }
}

void setup() {
  FastLED.setBrightness(brightness);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order
  FastLED.clear(true);
  FastLED.show();
  
  btn.register_shortPush(toggleLight);
  btn.register_longPush(Button::empty_callback);
  btn.register_stopPush(cycleAnim);

  anim = &anim_rand;
}

void loop()
{
  unsigned long now = millis();
  
  btn.tick(now);
  if(!light_on)
  {
    return;
  }
  
  anim->animate(now);
  FastLED.show();
}
