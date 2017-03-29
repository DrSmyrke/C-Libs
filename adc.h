#include <avr/interrupt.h>
#include <avr/io.h>
float vcc;
//ADC End of Conversion interrupt 
ISR(ADC_vect){
	unsigned char adc_data;
	adc_data = ADC>>2; //read 8 bit value 
	vcc = 1.1 * 255 / adc_data;
	if(!menu){
		sprintf(buff, "%f V",vcc);lcd_goto_xy(1,1);lcd_str(buff);
	}
}
void adc_init(){ 
	ADMUX = 0xE; //Set the Band Gap voltage as the ADC input
	ADCSRA = (1<<ADEN)|(1<<ADFR)|(1<<ADIE)|(1<<ADSC)|5;
}