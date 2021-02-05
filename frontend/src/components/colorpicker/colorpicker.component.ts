import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
	selector: 'app-colorpicker',
	templateUrl: './colorpicker.component.html',
	styleUrls: ['./colorpicker.component.css']
})
export class ColorPickerComponent {
	@Input() label: string = '';
	@Input() color: string = '#ff0000';
	@Output() value = new EventEmitter<string>();

	public submitValue($event: any) {
		this.color = $event.target.value;
		this.value.emit(this.color);
	}
}
