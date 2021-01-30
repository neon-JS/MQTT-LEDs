import { Component, OnInit } from '@angular/core';
import { LedDevice } from '../../models/Environment';
import { LedService } from '../../services/led/led.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {
  public devices: Array<LedDevice>;

  public constructor(private ledService: LedService) {
    this.devices = [];
  }

  public ngOnInit() {
    this.devices = this.ledService.getDevices();
  }
}
