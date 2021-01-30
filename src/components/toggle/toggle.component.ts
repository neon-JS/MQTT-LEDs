import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
	selector: 'app-toggle',
	templateUrl: './toggle.component.html',
	styleUrls: ['./toggle.component.css']
})
export class ToggleComponent {
	@Input() label: string = '';
	@Output() value = new EventEmitter<boolean>();

	public submitValue($event: any) {
		this.value.emit($event.target.checked);
	}
}
