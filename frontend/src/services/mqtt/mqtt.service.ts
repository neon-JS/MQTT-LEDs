import { Injectable, OnDestroy } from '@angular/core';
import { ISubscriptionGrant, MqttClient, QoS } from 'mqtt';
import { Observable } from 'rxjs';
import { filter, map } from 'rxjs/operators';
import { environment } from '../../environments/environment';
import { MqttMessage } from '../../models/MqttMessage';

declare const mqtt: any;

@Injectable({
  providedIn: 'root'
})
export class MqttService implements OnDestroy {
  private client?: MqttClient;
  private newMessage$: Observable<MqttMessage>;

  constructor() {
    this.newMessage$ = new Observable<MqttMessage>(observer => {
      this.getClient().on('message', (topic, payload) => observer.next({ topic, payload: payload.toString() }));
    });
  }

  public ngOnDestroy() {
    this.client?.end();
  }

  public publish(topic: string, payload: string, qos: QoS = 0) {
    this.getClient().publish(
      topic,
      payload,
      { qos },
      (error) => {
        if (error) {
          throw error;
        }
      }
    );
  }

  public topic(topic: string, qos: QoS = 0): Observable<string> {
    this.getClient().subscribe(
      topic,
      { qos, nl: true },
      (error: Error, granded: Array<ISubscriptionGrant>) => {
        if (error) {
          throw error;
        }

        if (granded.length === 0) {
          throw new Error('Topic not granted by server!');
        }
      }
    );

    return this.newMessage$
      .pipe(filter((message: MqttMessage) => message.topic === topic))
      .pipe(map((message: MqttMessage): string => message.payload));
  }

  /**
   * Returns the MqttClient that should be used to communicate with the broker.
   * Use this method rather than accessing the property directly as this allows us to lazy-load the client
   * instead of connecting in the constructor which may not be necessary at all!
   */
  private getClient(): MqttClient {
    if (!this.client) {
      this.client = mqtt.connect(environment.mqtt.host, { username: environment.mqtt.username, password: environment.mqtt.password });
    }

    return this.client!;
  }
}
