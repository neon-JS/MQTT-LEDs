interface MqttConfig {
    host: string;
    username: string;
    password: string;
}

export interface Environment {
    production: boolean;
    mqtt: MqttConfig;
}