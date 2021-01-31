#define TOPIC_COLOR "/some/matching/topic/color"
#define TOPIC_BRIGHTNESS "/some/matching/topic/brightness"
#define TOPIC_STATUS "/some/matching/topic/status"
#define TOPIC_EFFECT "/some/matching/topic/effect"

#define STATUS_OFF "off"
#define STATUS_ON "on"

#define EFFECT_FADING "fading"
#define EFFECT_RAINBOW "rainbow"

/* Number of cycles between two effect states.
 * This is necessary as the effect runs non-blocking. */
#define EFFECT_PAUSE_COUNT 25000

/* If set to true, the Arduino will be controlled via Serial communication only.
 * MQTT data must be transferred in the form of "`/some/topic;my-payload\n`".
 * Note that - even if set to false - the Arduino will send messages over Serial 
 * in case of MQTT errors! */
#define USE_SERIAL true
#define SERIAL_BAUD_RATE 115200

#define LED_COUNT 1
#define LED_DATA_PIN 1

/* Will be used if USE_SERIAL is set to false only. */
#define WLAN_SSID ""
#define WLAN_PASSWORD ""
#define MQTT_HOST ""
#define MQTT_PORT 1
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""