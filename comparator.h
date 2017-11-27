#include <avr/interrupt.h>
/*	ACSR

ACD (Analog Comparator Disable) - включение компаратора. 1 - запрещает работу аналогового компаратора, 0 - разрешает. По умолчанию компаратор всегда включен. Для уменьшения энергопотребления в спящих режимах, его рекомендуется отключать. При изменении бита ACD нужно запрещать прерывания компаратора, сбрасывая бит ACIE. В противном случае может произойти прерывание.

ACBG (Analog Comparator Bandgap Select) - подключение внутреннего источника опорного напряжения (ИОН) на 2.56 В к положительному входу компаратора (AIN0). 1 - подключает ИОН, 0 - отключает. 

ACO (Analog Comparator Output) - этот бит хранит состояние выхода аналогового компаратора, то есть результат сравнения входных напряжений. 

ACI (Analog Comparator Interrupt Flag) - флаг прерывания. Он устанавливается аппаратно, когда происходит событие определенное битами ACIS1 и ACIS0. Если прерывания компаратора разрешены, то вызывается обработчик. Флаг ACI сбрасывается аппаратно при выполнении обработчика. Также он может быть очищен программно, если записать в него 1.

ACIE (Analog Comparator Interrupt Enable) - разрешение прерываний компаратора. Когда этот бит установлен в 1 и прерывания разрешены глобально ( установлен флаг I регистра SREG), компаратор генерирует запрос на прерывание при изменении состояния его выхода. 

ACIC (Analog Comparator Input Capture Enable) - подключает выход компаратора к схеме захвата таймера Т1. 1 - выход компаратора подключен к схеме захвата, 0 - не подключен.

ACIS1, ACIS0 (Analog Comparator Interrupt Mode Select) - эти биты определяют событие, по которому будет вызываться прерывание компаратора. Все варианты перечислены в таблице.

ACIS1	ACIS0	Event
0		0		Любое изменение состояния выхода компаратора
0		1		Not USED
1		0		Выход компаратора меняется с 1 на 0
1		1		Выход компаратора меняется с 0 на 1

*/
ISR( ANA_COMP_vect ){
	digitalWrite(POWER_LED_PORT,POWER_LED_PIN_NUM,!CheckBit(ACSR,ACO));
	/*срабатывание по положительному 
    фронту входного сигнала */ 
	//if (!(ACSR &(1<<ACIS0))){
		
	//}else{
		/*срабатывание по отрицательному 
         фронту входного сигнала */
	//}
	//на всякий случай сброс флага прерывания     
	ACSR |=(1<<ACI);
}
void comparator_init()
{
	//pinModePD(6,INPUT);
	pinModePD(7,INPUT);
	ACSR |= ( 0 << ACD ) | ( 1 << ACBG ) | ( 1 << ACIE );
}
