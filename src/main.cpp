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

Animation *anim = nullptr;

static void dim();
static void turnDim();
static void cycleAnim();

enum struct LightState
{
  off,
  on,
  shutting_down
};

LightState light_state = LightState::off;
bool dim_up = true;

static void shut_down(unsigned long now, bool begin)
{
  static unsigned long last_time;
  static uint8_t step = 255;
  if(begin)
  {
    step = 255;
  }

  if(last_time + 50 < now)
  {
    last_time = now;
    for(uint8_t i = 0; i < NUM_LEDS; i++)
    {
      leds[i].subtractFromRGB(1);
    }

    step--;
    if(0 == step)
    {
      light_state = LightState::off;
      FastLED.clear(true);
    }
  }
}

void toggleLight()
{
  switch(light_state)
  {
  default:
  case LightState::off:
    light_state = LightState::on;
    btn.register_longPush(dim);
    btn.register_stopPush(turnDim);
    break;
  case LightState::on:
    light_state = LightState::shutting_down;
    btn.register_longPush(Button::empty_callback);
    btn.register_stopPush(cycleAnim);
    settings.store();
    shut_down(0, true);
    break;
  }
}

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

  switch(light_state)
  {
  default:
    return;
  case LightState::on:
    anim->animate(now);
    break;
  case LightState::shutting_down:
    shut_down(now, false);
    break;
  }
  FastLED.show();
}
