#include <avr/interrupt.h>
ISR(TIMER2_OVF_vect){
// TCNT2=0x05; //начальное значение таймера
	if(second++>=59){
		second=0;
		minute++;
	}
	if(minute>59){
		minute=0;
		hour++;
	}
	if(hour>23){hour=0;}

	lcd_goto_xy(1,1);
	if(hour<10){lcd_str("0");}
	itoa(hour,str,10);
	lcd_str(str);
	lcd_str(":");
	if(minute<10){lcd_str("0");}
	itoa(minute,str,10);
	lcd_str(str);
	lcd_str(":");
	if(second<10){lcd_str("0");}
	itoa(second,str,10);
	lcd_str(str);

	//
	if(hour<10){
		lcd_chrNum(0,1,2);
		lcd_chrNum(hour,17,2);
	}else{
		lcd_chrNum(hour/10,1,2);
		lcd_chrNum(hour-((hour/10)*10),17,2);
	}
	lcd_goto_xy_exact(33,3);
	lcd_str(":");
	if(minute<10){
		lcd_chrNum(0,39,2);
		lcd_chrNum(minute,55,2);
	}else{
		lcd_chrNum(minute/10,39,2);
		lcd_chrNum(minute-((minute/10)*10),55,2);
	}
	lcd_goto_xy_exact(70,3);
	lcd_str(":");
	lcd_goto_xy_exact(74,3);
	if(second<10){lcd_str("0");}
	itoa(second,str,10);
	lcd_str(str);
}
void t2_init(){
	TIMSK &= ~(1 << OCIE2)|(1 << TOIE2); // Запрещаем прерывания по T2
	ASSR |= (1 << AS2); // Включаем асинхронный режим T2
	TCNT2 = 0; // Сбрасываем регистр счета
	TCCR2 |= (1 << CS22)|(1 << CS20); // Предделитель на 128(32768/128 = 256 тиков/c)
	// Global enable interrupts
	sei();
	TIMSK |= (1 << TOIE2); // Разрешаем прерывание по переполнению Т2
}
