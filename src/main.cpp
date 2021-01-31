#include <Arduino.h>
#include <main.h>
#if USE_SERIAL == true
  #include <serial.h>
#else
  #include <mqtt.h>
#endif
#include <FastLED.h>

void setup();
void loop();
void ledLoop();
void handleMessage(Message *message);
void handleColorMessage(Message *message);
void handleBrightnessMessage(Message *message);
void handleStatusMessage(Message *message);
void handleEffectMessage(Message *message);

enum EffectId
{
    EFFECT_ID_NONE = 0,
    EFFECT_ID_FADING = 1,
    EFFECT_ID_RAINBOW = 2
};

EffectId currentEffect;
long effectStatus;
int pauseCount;
CRGB leds[LED_COUNT];
int brightness;

void setup()
{
  currentEffect = EFFECT_ID_NONE;
  effectStatus = 0;
  pauseCount = 0;
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, LED_COUNT);

  communicationInitialize();
}

void loop()
{
  ledLoop();
  communicationLoop();

  Message *next = communicationGetNextMessage();
  if (next == NULL)
  {
    return;
  }

  handleMessage(next);
  freeMessage(next);
}

void ledLoop()
{
  if (pauseCount < EFFECT_PAUSE_COUNT)
  {
    pauseCount += 1;
    return;
  }
  pauseCount = 0;

  if (currentEffect == EFFECT_ID_NONE)
  {
    return;
  }
  else if (currentEffect == EFFECT_ID_FADING)
  {
    effectStatus = (effectStatus < 255) ? effectStatus + 1 : 0;

    fill_solid(leds, LED_COUNT, CHSV(effectStatus, 255, 255));
    FastLED.show();
  }
  else if (currentEffect == EFFECT_ID_RAINBOW)
  {
    effectStatus = (effectStatus < 255) ? effectStatus + 1 : 0;

    fill_rainbow(leds, LED_COUNT, effectStatus, 255 / LED_COUNT);
    FastLED.show();
  }
}

void handleMessage(Message *message)
{
  if (strcmp(message->topic, TOPIC_COLOR) == 0)
  {
    handleColorMessage(message);
  }
  else if (strcmp(message->topic, TOPIC_BRIGHTNESS) == 0)
  {
    handleBrightnessMessage(message);
  }
  else if (strcmp(message->topic, TOPIC_STATUS) == 0)
  {
    handleStatusMessage(message);
  }
  else if (strcmp(message->topic, TOPIC_EFFECT) == 0)
  {
    handleEffectMessage(message);
  }
}

void handleColorMessage(Message *message)
{
  long colorValue = strtol(message->payload, NULL, 16);
  if (colorValue < 0 || colorValue > 0xFFFFFF)
  {
    return;
  }

  currentEffect = EFFECT_ID_NONE;
  fill_solid(leds, LED_COUNT, CRGB(colorValue));
  FastLED.show();
}

void handleBrightnessMessage(Message *message)
{
  long brightnessValue = strtol(message->payload, NULL, 10);
  if (brightnessValue < 0 || brightnessValue > 100)
  {
    return;
  }

  currentEffect = EFFECT_ID_NONE;
  brightness = (long)brightnessValue * 2.55;
  
  for (int i = 0; i < LED_COUNT; i++)
  {
    leds[i] %= brightness;
  }
  FastLED.show();
}

void handleStatusMessage(Message *message)
{
  bool newStatusOn = strcmp(message->payload, STATUS_ON) == 0;
  bool newStatusOff = strcmp(message->payload, STATUS_OFF) == 0;

  if (newStatusOn == newStatusOff)
  {
    // invalid value
    return;
  }

  currentEffect = EFFECT_ID_NONE;
  
  for (int i = 0; i < LED_COUNT; i++)
  {
    leds[i] %= newStatusOn ? brightness : 0;
  }
    FastLED.show();
}

void handleEffectMessage(Message *message)
{
  if (strcmp(message->payload, EFFECT_FADING) == 0)
  {
    effectStatus = 0;
    currentEffect = EFFECT_ID_FADING;
  }
  else if (strcmp(message->payload, EFFECT_RAINBOW) == 0)
  {
    effectStatus = 0;
    currentEffect = EFFECT_ID_RAINBOW;
  }
}