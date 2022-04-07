#include "adc.h"
#include <support_defines.h>

//--- VARIABLES -----------------------------------------------------------------------------
uint16_t vcc3				= 0;
uint16_t vcc5				= 0;
uint8_t adc_intFlag			= 0;
uint8_t analog_reference	= 1;
uint8_t adcPin				= 3;
uint8_t low					= 0;
uint8_t high				= 0;

//--- FUNCTIONS -----------------------------------------------------------------------------
void adc_init(void)
{
	pinModePC( 3, INPUT );
	pinModePC( 5, INPUT );
	// ADMUX = 0b00000101;
	// // ADMUX = 0b00000011;
	// ADMUX |= (1<<REFS1);
	// ADMUX |= (1<<REFS0);
	ADCSRA = 0;
	ADCSRA |= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS2);//|(1<<ADPS0);//|(1<<ADIE);
}

//--------------------------------------------------------------------------------------------
void adc_readData(void)
{
	low = ADCL;
	high = ADCH;

	if( adcPin == 5 ){
	// if( ADMUX << 5 == 5 ){
		// vcc5 = ( ADCH << 8 ) | ( ADCL );
		// vcc5 = ADC;
		vcc5 = (high << 8) | low;
	}else{
		// vcc3 = ( ADCH << 8 ) | ( ADCL );
		// vcc3 = ADC;
		vcc3 = (high << 8) | low;
	}
}

//--------------------------------------------------------------------------------------------
void adc_run(void)
{
	switch( adcPin ){
		case 3: adcPin = 5; break;
		case 5: adcPin = 3; break;
	}

	ADMUX = (analog_reference << 6) | (adcPin & 0x07);

	//Запускаем ADC
	ADCSRA |= (1<<ADSC);
	adc_intFlag = 0;
	//Ждем окончания преобразования
	if( !CheckBit( ADCSRA, ADIE ) ){
		while((ADCSRA & (1<<ADSC)));
		adc_readData();
	}
}

//--------------------------------------------------------------------------------------------
ISR( ADC_vect )
{
	adc_readData();
	adc_intFlag = 1;
}

//--------------------------------------------------------------------------------------------
uint8_t adc_isLight(void)
{
	//Проверка на наличие света
	return ( ADC > 230 ) ? 0x01 : 0x00;
}

