#include "FastLED.h"

// define the number of LEDs
#define NUM_LEDS 32
#define PIN 10

CRGB leds[NUM_LEDS];
CRGB color[3];

void setup() {
  //setting maximum brightness
  FastLED.setBrightness(80);

  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LEDS); //GRB for the WS2812 color order

  //reset all the LEDs
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));
  FastLED.show();

  color[0] = CRGB::Red;
  color[1] = CRGB::Green;
  color[2] = CRGB::Blue;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
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
    }
    digitalWrite(LED_BUILTIN, LOW);
    leds[iLED] = CRGB::Black;
    FastLED.show();
    delay(200);
  }
}
