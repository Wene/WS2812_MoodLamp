#include "FastLED.h"

#define NUM_LEDS 32
#define DATA_PIN 10
#define SWITCH_PIN 9

CRGB leds[NUM_LEDS];
CRGB color[3];

void setup() {
  //setting maximum brightness
  FastLED.setBrightness(80);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order

  //reset all the LEDs
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
  FastLED.show();

  color[0] = CRGB::Red;
  color[1] = CRGB::Green;
  color[2] = CRGB::Blue;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop()
{
  for (int iLED = 0; iLED < NUM_LEDS; iLED++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    for (int iColor = 0; iColor < 3; iColor++)
    {
      leds[iLED] = color[iColor];
      FastLED.show();
      delay(200);
      while(digitalRead(SWITCH_PIN) == LOW)
      {
        delay(100);
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    leds[iLED] = CRGB::Black;
    FastLED.show();
    delay(200);
  }
}
