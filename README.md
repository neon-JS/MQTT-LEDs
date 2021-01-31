# MµTT-LEDs
Arduino / ESP 8266 script that listens to MQTT and controls LEDs.

## About
This script is the counterpart to the [MQTT-LED-Controller](https://github.com/neon-JS/MQTT-LED-Controller) frontend which allows controlling the LEDs in a browser. The Arduino connects to an MQTT server and listens to certain topics. It will set the LEDs state accordingly to incoming messages.

The Arduino can also be connected to via Serial communication, in which case the MQTT data must be transferred in the form of "`/some/topic;my-payload\n`". To use this, set `#define USE_SERIAL true`.

## Protocol
See section [Protocol](https://github.com/neon-JS/MQTT-LED-Controller/blob/master/README.md#protocol) of the [MQTT-LED-Controller](https://github.com/neon-JS/MQTT-LED-Controller).

## Installation
1. Clone this repository.
2. Open it up in PlatformIO.
3. Set up _include/main.h_ according to your needs.
4. Run _PlatformIO: Upload_ or whatever.

# Used libraries
- [Arduino Client for MQTT ("pubsubclient")](https://pubsubclient.knolleary.net), licensed under the MIT License.
- [FastLED Animation Library](http://fastled.io), licensed under the MIT License.

# License
Licensed under the MIT License.