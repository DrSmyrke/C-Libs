#ifndef _SUPPORT_DEFINES_H_
#define _SUPPORT_DEFINES_H_

#include <avr/io.h>

//#define TASCII(numb) (numb+48)
//#define DIG(numb) (numb/10)
//#define DEC(numb) (numb%10)

#define true					1
#define false					0

#define INPUT					0
#define INPUT_RESTOVCC			2
#define OUTPUT					1
#define pinModePD(bit,mode) {if(mode==INPUT){setZero(DDRD,bit);setZero(PORTD,bit);}if(mode==OUTPUT){setPlus(DDRD,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRD,bit);setPlus(PORTD,bit);}}
#define pinModePB(bit,mode) {if(mode==INPUT){setZero(DDRB,bit);setZero(PORTB,bit);}if(mode==OUTPUT){setPlus(DDRB,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRB,bit);setPlus(PORTB,bit);}}
#define pinModePC(bit,mode) {if(mode==INPUT){setZero(DDRB,bit);setZero(PORTC,bit);}if(mode==OUTPUT){setPlus(DDRC,bit);}if(mode==INPUT_RESTOVCC){setZero(DDRC,bit);setPlus(PORTC,bit);}}

#define digitalWrite(port,bit,mode) {if(mode==0){setZero(port,bit);}if(mode==1){setPlus(port,bit);}}

#define setPlus(reg,bit) reg |= (1<<bit)
#define setZero(reg,bit) reg &= ~(1<<bit)
#define ibi(reg,bit) reg ^= (1<<bit)
#define CheckBit(reg,bit) (reg&(1<<bit))

#endif // _SUPPORT_DEFINES_H_
