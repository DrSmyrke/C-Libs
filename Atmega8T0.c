#include "Atmega8T0.h"

#include <avr/interrupt.h>
#include <avr/io.h>

uint8_t ms100Flag = 0;
uint8_t secondFlag = 0;
unsigned short t0_counter = 0;
unsigned short t0_counter2 = 0;

ISR( TIMER0_OVF_vect )
{
	if( t0_counter2 < 3125 ){
		t0_counter2++;
	}else{
		//100ms
		t0_counter2 = 0;
		ms100Flag = 1;
	}
	if( t0_counter < 31250 ){
		t0_counter++;
	}else{
		//second
		t0_counter = 0;
		secondFlag = 1;
	}
}

void t0_reset(void)
{
	TCNT0			= 0x00;
	ms100Flag		= 0;
	secondFlag		= 0;
	t0_counter		= 0;
	t0_counter2		= 0;
}

void t0_init(void)
{
	TCCR0|=(1<<CS00);		//предделитель/1
	TIMSK|=(1<<TOIE0);		// Разрешаем прерывание по переполнению Т0
	t0_reset();
}

