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

bool pause = false;
void togglePause()
{
  pause = !pause;
}
int long_count = 0;
void indicateLong()
{
  long_count++;
  Serial.println(long_count);
}

void setup() {
  //setting maximum brightness
  FastLED.setBrightness(80);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order

  //reset all the LEDs
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
  FastLED.show();

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  btn.register_shortPush(togglePause);
  btn.register_longPush(indicateLong);
}

unsigned long last_time = 0;
bool led_state = false;

void loop()
{
  unsigned long now = millis();
  
  btn.tick(now);
  lava.animate(now);
  if(pause)
  {
    return;
  }
  
  if(now > last_time + 200)
  {
    last_time = now;
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
  }
  
}
