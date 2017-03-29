//#define TASCII(numb) (numb+48)
//#define DIG(numb) (numb/10)
//#define DEC(numb) (numb%10)

#define true 1
#define false 0

#define INPUT 0
#define INPUT_RESTOVCC 2
#define OUTPUT 1
#define pinModePD(bit,mode) {if(mode==INPUT){setZero(DDRD,bit);setZero(PORTD,bit);}if(mode==OUTPUT){setPlus(DDRD,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRD,bit);setPlus(PORTD,bit);}}
#define pinModePB(bit,mode) {if(mode==INPUT){setZero(DDRB,bit);setZero(PORTB,bit);}if(mode==OUTPUT){setPlus(DDRB,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRB,bit);setPlus(PORTB,bit);}}
#define pinModePC(bit,mode) {if(mode==INPUT){setZero(DDRB,bit);setZero(PORTC,bit);}if(mode==OUTPUT){setPlus(DDRC,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRC,bit);setPlus(PORTC,bit);}}

#define digitalWrite(port,bit,mode) {if(mode==0){setZero(port,bit);}if(mode==1){setPlus(port,bit);}}

#define setPlus(reg,bit) reg |= (1<<bit)
#define setZero(reg,bit) reg &= ~(1<<bit)
#define ibi(reg,bit) reg ^= (1<<bit)
#define CheckBit(reg,bit) (reg&(1<<bit))
#define nop() {asm("nop");}		// функция асемблера для задержки
void delay(int t){			// функция задержки
	int x;
	for (x=t;x>0;x--) nop(); 
}
// Функция задержки в мкс
void _delay_us(unsigned char time_us)
{
	register unsigned char i;
	for(i = 0; i < time_us; i++){
		asm volatile(" PUSH  R0 ");
		asm volatile(" POP   R0 ");
	}
}
 // Функция задержки в мс
void _delay_ms(unsigned int time_ms)
{
	register unsigned int i;
	for(i = 0; i < time_ms; i++){
		_delay_us(250);
		_delay_us(250);
		_delay_us(250);
		_delay_us(250);
	}
}
