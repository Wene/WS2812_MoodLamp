#include <Arduino.h>
#include <FastLED.h>
#include "button.h"
#include "anim_rand.h"
#include "anim_lava.h"
#include "anim_white.h"
#include "settings.h"

#define NUM_LEDS 32
#define DATA_PIN 10
#define BUTTON_PIN 9

CRGB leds[NUM_LEDS];

Button btn(BUTTON_PIN);

Settings settings;

static void dim();
static void turnDim();
static void cycleAnim();

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
    settings.store();
  }
}

bool dim_up = true;
static void turnDim()
{
  dim_up = !dim_up;
}

static void dim()
{
  int16_t brightness = settings.getBrightness();
  int8_t step = brightness / 20;
  step++;   // make sure step is at least 1 when below 20

  if(dim_up)
  {
    brightness += step;
  }
  else
  {
    brightness -= step;
  }

  if(brightness > 255)
  {
    brightness = 255;
  }
  else if(brightness < 1)
  {
    brightness = 1;
  }

  FastLED.setBrightness(brightness);

  settings.setBrightness(brightness);
}

Animation *anim = nullptr;

static void createAnim()
{
  uint8_t anim_no = settings.getAnimation(2);
  delete anim;
  switch(anim_no)
  {
    default:
    case 0:
      anim = new Lava(leds, NUM_LEDS);
    break;
    case 1:
      anim = new Rand(leds, NUM_LEDS);
    break;
    case 2:
      anim = new White(leds, NUM_LEDS);
    break;
  }
}

static void cycleAnim()
{
  uint8_t anim_no = settings.getAnimation(2);
  if(++anim_no > 2)
  {
    anim_no = 0;
  }
  settings.setAnimation(anim_no);
  createAnim();
}

void setup() {
  FastLED.setBrightness(settings.getBrightness());
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order
  FastLED.clear(true);
  FastLED.show();
  
  btn.register_stopPush(cycleAnim);
  createAnim();

  btn.register_shortPush(toggleLight);
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
