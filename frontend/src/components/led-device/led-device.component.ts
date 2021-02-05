import { Component, Input } from '@angular/core';
import { LedDevice } from '../../models/Environment';
import { LedService } from '../../services/led/led.service';

@Component({
  selector: 'app-led-device',
  templateUrl: './led-device.component.html',
  styleUrls: ['./led-device.component.scss']
})
export class LedDeviceComponent {
  @Input()
  public device: LedDevice = { name: '', topicPrefix: '', topics: { brightness: '', color: '', effect: '', status: '' }, effects: [] };

  constructor(private ledService: LedService) {
  }

  public updateColor(color: string) {
    this.ledService.setColor(this.device, color.replace(/#/g, ''));
  }

  public updateBrightness(brightness: number) {
    this.ledService.setBrightness(this.device, brightness);
  }

  public updateStatus(active: boolean) {
    this.ledService.setStatus(this.device, active);
  }

  public updateEffect(effect: string) {
    this.ledService.setEffect(this.device, effect);
  }
}
