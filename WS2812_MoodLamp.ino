#include "FastLED.h"
#include "button.h"
#include "anim_lava.h"

namespace a = animation;

#define NUM_LEDS 32
#define DATA_PIN 10
#define BUTTON_PIN 9

CRGB leds[NUM_LEDS];

Button btn(BUTTON_PIN);
a::Lava lava(leds, NUM_LEDS);

void reset_leds()
{
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
  FastLED.show();
}

bool light_on = false;
void toggleLight()
{
  light_on = !light_on;
  if(!light_on)
  {
    reset_leds();
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

void setup() {
  FastLED.setBrightness(brightness);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order

  reset_leds();
  
//  Serial.begin(115200);

//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, LOW);

  btn.register_shortPush(toggleLight);
  btn.register_longPush(dim);
  btn.register_stopPush(turnDim);
}

unsigned long last_time = 0;

void loop()
{
  unsigned long now = millis();
  
  btn.tick(now);
  if(!light_on)
  {
    return;
  }
  lava.animate(now);
}
