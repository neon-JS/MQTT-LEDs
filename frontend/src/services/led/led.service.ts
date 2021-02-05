import { Injectable } from '@angular/core';
import { MqttService } from '../mqtt/mqtt.service';
import { LedDevice } from '../../models/Environment';
import { environment } from '../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class LedService {

  constructor(
    private mqttService: MqttService
  ) { }

  public getDevices(): Array<LedDevice> {
    return environment.ledDevices;
  }

  public setColor(device: LedDevice, color: string) {
    if (!color.match(/^[0-9a-fA-F]{6}$/m)) {
      throw new Error('Invalid color value given!');
    }

    this.mqttService.publish(`${device.topicPrefix}${device.topics.color}`, color);
  }

  public setBrightness(device: LedDevice, brightness: number) {
    if (!Number.isInteger(brightness) || brightness < 0 || brightness > 100) {
      throw new Error('Invalid brightness value given!');
    }

    this.mqttService.publish(`${device.topicPrefix}${device.topics.brightness}`, brightness.toString());
  }

  public setEffect(device: LedDevice, effect: string) {
    if (!device.effects.map(effect => effect.identifier).includes(effect)) {
      throw new Error('Effect not available for device!');
    }

    this.mqttService.publish(`${device.topicPrefix}${device.topics.effect}`, effect);
  }

  public setStatus(device: LedDevice, active: boolean) {
    this.mqttService.publish(`${device.topicPrefix}${device.topics.status}`, active ? 'on' : 'off');
  }
}
