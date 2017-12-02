#include <avr/interrupt.h>
#include <avr/io.h>

uint8_t counter = 0;
//функция обработчик внешнего прерывания INT0
ISR( INT0_vect )
{
  counter++;
}
//настройка внешнего прерывния INT0
void int0_init(void)
{
	//настраиваем на срабатывание INT0 по переднему фронту
	MCUCR |= (1<<ISC01)|(1<<ISC00);
	//разрешаем внешнее прерывание INT0 
	GICR |= (1<<INT0);
	sei();
}
