#include <avr/interrupt.h>
#include <avr/io.h>
/*
		ADCSRA:
Bit:			ADEN	ADSC	ADFR	ADIF	ADIE	ADPS2	ADPS1	ADPS0
Read/Write:		r/w		r/w		r/w		r/w		r/w		r/w		r/w		r/w
Initial Value:	0		0		0		0		0		0		0		0


    Бит ADEN включает и выключает АЦП микроконтроллера.

           ADEN = 1 — АЦП включен.

           ADEN = 0 — АЦП выключен.

    При записи 1 в бит ADSC, в режиме однократного преобразования запускается преобразование.
    Бит ADFR, отвечает за выбор режима преобразования.

           ADFR = 1 — Непрерывное преобразование.

           ADFR = 0 — Однократное преобразование.

    Бит ADIF, флаг окончания преобразования, становится равен 1 при окончании преобразования
    Бит ADIE, разрешает прерывание АЦП.

           ADIE = 1 — Прерывание разрешено.

           ADIE = 0 — Прерывание запрещено.

    Биты ADPS0-ADPS2 отвечают за выбор предделителя между частотой тактирования микроконтроллера и АЦП.
ADPS2	ADPS1	ADPS0	Value
0		0		0		2
0		0		1		2
0		1		0		4
0		1		1		8
1		0		0		16
1		0		1		32
1		1		0		64
1		1		1		128
Результат преобразования помещается в пару регистров ADCH и ADCL, в виде заданным значением бита ADLAR.
*/


//float vcc;
int16_t vcc;
ISR(ADC_vect){
	vcc = ADCW;
	//vcc = ADCW*(4.9/1023.0);
// 	unsigned char adc_data;
// 	adc_data = ADC>>2;
// 	vcc = 1.1 * 255 / adc_data;
//Результат преобразования хранится в ADCW = ADCH:ADCL
	//unsigned int v = (ADCL|ADCH<<8);
}
void adc_init()
{
	pinModePC(0,INPUT); 
	ADMUX = 0b00000000;
	ADMUX |= (1<<REFS0);
	//ADMUX |= (1<<REFS1);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADIE);
}

void adc_run()
{
	//Запускаем ADC
	ADCSRA |=(1<<ADSC);
	//Ждем окончания преобразования
	while((ADCSRA & (1<<ADSC)));
}

uint8_t adc_isLight()
{
	//Проверка на наличие света
	return ( ADC > 750 ) ? 0x01 : 0x00;
}
