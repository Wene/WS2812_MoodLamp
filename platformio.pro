win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/Projects/Arduino/WS2812_MoodLamp/include"
INCLUDEPATH += "$${HOMEDIR}/Projects/Arduino/WS2812_MoodLamp/src"
INCLUDEPATH += "$${HOMEDIR}/Projects/Arduino/WS2812_MoodLamp/.pio/libdeps/pro16MHzatmega328/FastLED/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/variants/eightanaloginputs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/lib/rdm6300_ID5780/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/HID/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoavr/libraries/__cores__/arduino/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/avr/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=40304"
DEFINES += "ARDUINO_AVR_PRO"
DEFINES += "F_CPU=16000000L"
DEFINES += "ARDUINO_ARCH_AVR"
DEFINES += "ARDUINO=10805"
DEFINES += "__AVR_ATmega328P__"

OTHER_FILES += platformio.ini

SOURCES += src/anim_rand.cpp \
    src/animation.cpp
HEADERS += src/anim_lava.h
HEADERS += src/animation.h
SOURCES += src/button.cpp
HEADERS += src/anim_rand.h
HEADERS += src/button.h
SOURCES += src/main.cpp
SOURCES += src/anim_lava.cpp
