# MµTT-LEDs
Arduino / ESP 8266 script that connects to an MQTT broker and controls LEDs.

## About
This script is the counterpart to the _frontend_ project which allows controlling the LEDs in a browser. The Arduino connects to an MQTT broker and listens to certain topics. It will set the LEDs state accordingly to incoming messages.

The Arduino can also be connected to via Serial communication, in which case the MQTT data must be transferred in the form of "`/some/topic;my-payload\n`". To use this, set `#define USE_SERIAL true`.

## Protocol
See section [MQTT-Protocol](../README.md#mqtt-protocol) in the main README.md.

## Installation
1. Clone this repository.
2. Open it up in PlatformIO.
3. Set up _include/main.h_ according to your needs.
4. Run _PlatformIO: Upload_ or whatever.