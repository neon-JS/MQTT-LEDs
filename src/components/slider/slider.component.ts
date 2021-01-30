import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
	selector: 'app-slider',
	templateUrl: './slider.component.html',
	styleUrls: ['./slider.component.css']
})
export class SliderComponent {
	@Input() initial: number = 0;
	@Input() label: string = '';
	@Input() min: number = 0;
	@Input() max: number = 100;
	@Output() value = new EventEmitter<number>();

	public submitValue($event: any) {
		this.initial = parseInt($event.target.value);
		this.value.emit(this.initial);
	}
}
