#include <util/delay.h>
unsigned char Temp_H = 0,Temp_L = 0,OK_Flag = 0,temp_flag;
unsigned char DS18B20_init(void){
	PORTC &= ~(1 << PC0); // устанавливаем низкий уровень
	DDRC |= (1 << PC0);
	_delay_us(490);
	DDRC &= ~(1 << PC0);
	_delay_us(68);
	OK_Flag = (PINC & (1 << PC0)); // ловим импульс присутствия датчика
	// если OK_Flag = 0 датчик подключен, OK_Flag = 1 датчик не подключен
	_delay_us(422);
	return OK_Flag;
}
/*** Функция чтения байта из DS18B20 ***/
unsigned char read_18b20(void){
	unsigned char i;  
	unsigned char dat = 0;
	for(i = 0;i < 8;i++){      
		DDRC |= (1 << PC0);
		_delay_us(2);       
		DDRC &= ~(1 << PC0);
		_delay_us(4);       
		dat = dat >> 1;      
		if(PINC & (1 << PC0)){          
			dat |= 0x80;
		}
		_delay_us(62);
	}  
	return dat;
}
/*** функция записи байта в DS18B20 ***/
void write_18b20(unsigned char dat){
	unsigned char i;   
	for(i = 0;i < 8;i++){
		DDRC |= (1 << PC0);
		_delay_us(2);          
		if(dat & 0x01){
			DDRC &= ~(1 << PC0); 
		}else{
			DDRC |= (1 << PC0);
		}
		dat = dat >> 1;
		_delay_us(62);
		DDRC &= ~(1 << PC0);
		_delay_us(2);
	}  
}
