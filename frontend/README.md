# MQTT-LED-Controller
Controls LEDs in your Browser via (WebSocket-) MQTT using [MQTT.js](https://github.com/mqttjs/MQTT.js).

## How it works
This website connects to an MQTT server via WebSocket. (The MQTT protocol is _not_ supported via browser, sadly!) 
All available MQTT clients have to be configured in the Angular environment. Using a very simple MQTT "_protocol_", we can then send updates to the MQTT server for our LEDs. (More about that in [Protocol](#Protocol).)

## Protocol 
<a name="protocol"></a>
The configuration for each LED client contains a `topicPrefix`. This is the MQTT topic that the client is referred to (e.g. "_/floor/1/livingroom/led/1_"). 

Each LED client also has its own "_control topics_". Those will be used when sending updates for color, brightness, status or effect. Currently, there are four control topics: 

- color, e.g. `/color` with payload being some RGB-value (e.g. _ff00ff_).
- effect, e.g. `/effect` with payload being effect-identifier (e.g. _flashing_).
- brightness, e.g. `/brightness` payload being a value between _0 - 100_.
- status e.g. `/status` with payload being "_on_" / "_off_".

So if we're setting the LEDs in the living room to red, this will result in an MQTT message with topic _/floor/1/livingroom/led/1/color_ and payload _ff0000_.

### Effects
You can also configure certain effects that the LEDs can handle. Those could be effects like "flashing", "fading" etc. 

## Installation
1. Clone this repository.
2. Run `npm i` to install all [Angular](https://angular.io) dependencies.
3. Run `npm run build-mqtt` to build the [MQTT.js](https://github.com/mqttjs/MQTT.js) client and include it in the Angular project.
4. Edit the _src/environment/environment.ts_ so that it fits your needs. (You may want to see _src/models/Environment_ before as it contains some useful comments.)
5. Run `npm run build` or `npm run serve`.

## Used libraries
- [Angular 11](https://angular.io), licensed under the MIT License.
- [Bootstrap 5](https://getbootstrap.com), licensed under the MIT License.
- [MQTT.js 4.2.6](https://github.com/mqttjs/MQTT.js), licensed under the MIT License.

## License
Licensed under the MIT License.