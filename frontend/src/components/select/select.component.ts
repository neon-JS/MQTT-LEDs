import { Component, Input, Output, EventEmitter, OnInit } from '@angular/core';

@Component({
  selector: 'app-select',
  templateUrl: './select.component.html',
  styleUrls: ['./select.component.css']
})
export class SelectComponent implements OnInit {
  @Input() options: Array<any> = [];
  @Input() label: string = '';
  @Input() nameAttribute: string = '';
  @Input() firstAsDefault: boolean = false;
  @Output() value = new EventEmitter<any>();

  public selectedValue: any = null;

  update() {
    this.value.emit(this.selectedValue);
  }

  ngOnInit() {
    this.selectedValue = null;

    if (this.firstAsDefault && this.options.length > 0) {
      this.selectedValue = this.options[0];
    }
  }
}
