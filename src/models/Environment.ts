interface MqttConfig {
    host: string;           // e.g. "ws://300.300.300.300:8080/"
    username: string;
    password: string;
}

interface Effect {
    name: string;           // e.g. "Flashing"
    identifier: string;     // e.g. "flashing"
}

interface LedControlTopics {
    color: string;          // e.g. /color with payload being some RGB-value (e.g. "ff00ff")
    effect: string;         // e.g. /effect with payload being efect-identifier (e.g. "flashing")
    brightness: string;     // e.g. /brightness payload being a value between 0 - 100
    status: string;         // e.g. /status with payload being "on" of "off"
}

export interface LedDevice {
    name: string;           // e.g. "Living room LEDs"
    topicPrefix: string;    // e.g. /floor/1/livingroom/led/1
    effects: Array<Effect>;
    topics: LedControlTopics;
}

export interface Environment {
    production: boolean;
    mqtt: MqttConfig;
    ledDevices: Array<LedDevice>
} 