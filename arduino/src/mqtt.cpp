#include <main.h>

#if USE_SERIAL == false
#include <Arduino.h>
#include <mqtt.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void onMessageCallback(char *topic, byte *payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); // see https://github.com/knolleary/pubsubclient/issues/824
MessageQueue *messageQueue;

void communicationLoop()
{
    if(!mqttClient.loop()) {
        Serial.println("ERROR: MQTT client is not connected!");
    }
}
void communicationInitialize()
{
    messageQueue = messageQueueInitialize();

    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial)
    {
    }

    WiFi.mode(WIFI_STA); // Don't create Access Point (WIFI_AP)
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1);
    }

    // see https://github.com/knolleary/pubsubclient/issues/824
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCallback(onMessageCallback);

    if (!mqttClient.connect("MqttArduino", MQTT_USERNAME, MQTT_PASSWORD))
    {
        Serial.println("ERROR: Could not connect to MQTT server!");
        return;
    }

    if (!mqttClient.subscribe(TOPIC_COLOR)) {
        Serial.print("ERROR: Could not subscribe to colors' topic!");
    }
    if (!mqttClient.subscribe(TOPIC_BRIGHTNESS)) {
        Serial.print("ERROR: Could not subscribe to brightness' topic!");
    }
    if (!mqttClient.subscribe(TOPIC_STATUS)) {
        Serial.print("ERROR: Could not subscribe to status' topic!");
    }
    if (!mqttClient.subscribe(TOPIC_EFFECT)) {
        Serial.print("ERROR: Could not subscribe to effects' topic!");
    }
}
Message *communicationGetNextMessage()
{
    return messageQueueShift(messageQueue);
}

void onMessageCallback(char *topic, byte *payload, unsigned int length)
{
    /* see https://pubsubclient.knolleary.net/api#callback :
     * "Internally, the client uses the same buffer for both inbound and outbound messages. 
     *  After the callback function returns, or if a call to either publish or subscribe is made 
     *  from within the callback function, the topic and payload values passed to the function 
     *  will be overwritten. The application should create its own copy of the values if they are
     *  required after the callback returns." */
    char *copiedTopic = (char *)malloc(sizeof(char) * (strlen(topic) + 1));
    strcpy(copiedTopic, topic);
    copiedTopic[strlen(topic)] = 0;

    char *convertedPayload = (char *)malloc(sizeof(char) * (length + 1));
    for (unsigned int i = 0; i < length; i++)
    {
        convertedPayload[i] = (char)payload[i];
    }
    convertedPayload[length] = 0;

    Message *nextMessage = (Message *)malloc(sizeof(Message));
    nextMessage->topic = copiedTopic;
    nextMessage->payload = convertedPayload;

    messageQueuePush(messageQueue, nextMessage);
}

#endif