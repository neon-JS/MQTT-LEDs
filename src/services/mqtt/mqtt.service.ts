import { Injectable } from '@angular/core';
import { MqttClient } from 'mqtt';

@Injectable({
  providedIn: 'root'
})
export class MqttService {

  private client: MqttClient;

  constructor() { }
}
