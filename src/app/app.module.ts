import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from '../components/app/app.component';
import { LedDeviceComponent } from '../components/led-device/led-device.component';
import { ColorPickerComponent } from '../components/colorpicker/colorpicker.component';
import { SliderComponent } from '../components/slider/slider.component';
import { ToggleComponent } from '../components/toggle/toggle.component';
import { SelectComponent } from '../components/select/select.component';

@NgModule({
  declarations: [
    AppComponent,
    LedDeviceComponent,
    ColorPickerComponent,
    SliderComponent,
    ToggleComponent,
    SelectComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
