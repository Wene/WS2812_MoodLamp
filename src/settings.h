#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

class Settings
{
public:
  Settings();
  void store();
  uint8_t getBrightness();
  uint8_t getAnimation(uint8_t max);
  void setBrightness(uint8_t value);
  void setAnimation(uint8_t value);
private:
  bool changed;
  struct block
  {
    uint8_t level;
    uint8_t brightness;
    uint8_t animation;
  } data;
  size_t position;
};

#endif // SETTINGS_H
