# MQTT-LED-Controller
Controls the Arduino / ESP 8266 in your browser via (WebSocket-) MQTT using [MQTT.js](https://github.com/mqttjs/MQTT.js).

## How it works
This website connects to an MQTT broker via WebSocket. (The MQTT protocol is _not_ supported via browser, sadly!) 
All available Arduinos have to be configured in the Angular environment. Using a very simple MQTT "_protocol_", we can then send updates to the MQTT broker for our LEDs. (More about that in section [MQTT-Protocol](../README.md#mqtt-protocol) in the main README.md.)

### Effects
You can also configure certain effects that the LEDs can handle. Those could be effects like "flashing", "fading" etc. 

## Installation
1. Clone this repository.
2. Run `npm i` to install all [Angular](https://angular.io) dependencies.
3. Run `npm run build-mqtt` to build the [MQTT.js](https://github.com/mqttjs/MQTT.js) client and include it in the Angular project.
4. Edit the _src/environment/environment.ts_ so that it fits your needs. (You may want to see _src/models/Environment_ before as it contains some useful comments.)
5. Run `npm run build` or `npm run serve`.