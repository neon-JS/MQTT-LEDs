# MqttSerialConverter [WIP]
Listens to MQTT and forwards all received messages to a Serial port.

## What it does
This program connects to an MQTT broker and subscribes to _all_ topics. It also connects to a Serial port and 
forwards all received messages to it. The messages will be converted into the structure "`/some/topic;my-payload\n`".
An Arduino / ESP 8266 that has the option `USE_SERIAL` set to `true` will then receive and parse this messages.

## Why?!
The Arduino can be connected to a device that already has a connection to the MQTT broker, meaning that we don't
have to care about WLAN connections. It will also keep our network clean.

## Installation
**Currently TODO**