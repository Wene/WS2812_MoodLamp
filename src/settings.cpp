#include "settings.h"
#include <EEPROM.h>

Settings::Settings()
{
  block current = {.level = 0, .brightness = 30, .animation = 1};
  data = {};
  position = 0;
  bool found = false;

  while(position <= EEPROM.length() - sizeof(block))
  {
    block next;
    EEPROM.get(position, next);
    if(next.level < current.level || (next.level == 0xff && current.level == 0))  // current is the latest block
    {
      data = current;
      found = true;
      break;
    }
    position += sizeof(block);
    current = next;
  }

  if(!found)
  {
    data = current;   // take the data from the last block
    position = 0;     // and prepare to write to the first
    data.level++;
  }
}

void Settings::store()
{
  EEPROM.put(position, data);
  position += sizeof(block);
  if(position > EEPROM.length() - sizeof(block))
  {
    position = 0;
    data.level++;
  }
}

uint8_t Settings::getBrightness()
{
  return data.brightness >= 1 ? data.brightness : 1;
}

uint8_t Settings::getAnimation(uint8_t max)
{
  return data.animation <= max ? data.animation : max;
}

void Settings::setBrightness(uint8_t value)
{
  data.brightness = value;
}

void Settings::setAnimation(uint8_t value)
{
  data.animation = value;
}
