#include <avr/interrupt.h>
#include <avr/io.h>
float vcc;
//int16_t vcc;
ISR(ADC_vect){
	vcc = ADCW*(5/1023);
// 	unsigned char adc_data;
// 	adc_data = ADC>>2;
// 	vcc = 1.1 * 255 / adc_data;
}
void adc_init(){
	ADMUX = 0b01000011;
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|5;
	sei ();
}
