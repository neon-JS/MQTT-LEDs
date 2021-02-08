# MQTT-LEDs
Monorepo that contains projects to control LEDs from a browser via MQTT.

## About
This project is made to control RGB-LEDs via MQTT in a browser. The LEDs are wired to an Arduino or ESP 8266 and connected via Serial or WLAN. 

## Structure
The project is currently split into three sub-projects:
- _arduino/_ contains the code for controlling the LEDs on an Arduino / ESP 8266 via MQTT.
- _frontend/_ contains an Angular project for a website which connects to an MQTT broker (via Websocket) and allows us to send control-messages to the Arduino.
- _converter/_ contains a simple .NET program that listens to MQTT and forwards all received messages to a Serial port.

For more information, read the _README.md_ in the specific projects.

## MQTT-Protocol 
<a name="mqtt-protocol"></a>
The configuration for each LED client in the frontend contains a `topicPrefix`. This is the MQTT topic that the client is referred to (e.g. "_/floor/1/livingroom/led/1_"). 

Each LED client also has its own "_control topics_". Those will be used when sending updates for color, brightness, status or effect. Currently, there are four control topics: 

- color, e.g. `/color` with payload being some RGB-value (e.g. _ff00ff_).
- effect, e.g. `/effect` with payload being effect-identifier (e.g. _flashing_).
- brightness, e.g. `/brightness` payload being a value between _0 - 100_.
- status e.g. `/status` with payload being "_on_" / "_off_".

So if we're setting the LEDs in the living room to red, this will result in an MQTT message with topic _/floor/1/livingroom/led/1/color_ and payload _ff0000_.

## Used libraries
### Frontend
- [Angular 11](https://angular.io), licensed under the MIT License.
- [Bootstrap 5](https://getbootstrap.com), licensed under the MIT License.
- [MQTT.js 4.2.6](https://github.com/mqttjs/MQTT.js), licensed under the MIT License.
### Arduino
- [Arduino Client for MQTT ("pubsubclient")](https://pubsubclient.knolleary.net), licensed under the MIT License.
- [FastLED Animation Library](http://fastled.io), licensed under the MIT License.

## Converter (MQTT -> Serial)
- [MQTTnet](https://github.com/chkr1011/MQTTnet), licensed under the MIT License.

## License
Licensed under the MIT License.