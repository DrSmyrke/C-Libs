#include <avr/interrupt.h>
#include <avr/io.h>
//float vcc;
int16_t vcc;
ISR(ADC_vect){
	vcc = ADCW;
	//vcc = ADCW*(4.9/1023.0);
// 	unsigned char adc_data;
// 	adc_data = ADC>>2;
// 	vcc = 1.1 * 255 / adc_data;
}
void adc_init(){
	pinModePC(0,INPUT); 
	pinModePC(1,INPUT); 
	ADMUX = 0b01000000;
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|5;
	sei ();
}
