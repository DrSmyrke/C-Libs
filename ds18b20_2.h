#include <util/delay.h>
//определяем порт и бит к которому подключено устройство 1-wire
#define W1_PORT PORTC
#define W1_DDR DDRC
#define W1_PIN PINC
#define W1_BIT 5

//функция определяет есть ли устройство на шине
unsigned char w1_find(){
	unsigned char device;
	W1_DDR |= 1<<W1_BIT;
	_delay_us(485);
	W1_DDR &= ~(1<<W1_BIT);
	_delay_us(65);
	
	if((W1_PIN & (1<<W1_BIT)) ==0x00)
		device = 1;
	else
		device = 0;
	_delay_us(420);

	return device;
}
//функция посылает команду на устройство 1-wire
void w1_sendcmd(unsigned char cmd){
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		if((cmd & (1<<i)) == 1<<i)
		{
			W1_DDR |= 1<<W1_BIT;
			_delay_us(2);
			W1_DDR &= ~(1<<W1_BIT);			
			_delay_us(65);
		} 
		else
		{
			
			W1_DDR |= 1<<W1_BIT;
			_delay_us(65);
			W1_DDR &= ~(1<<W1_BIT);
			_delay_us(5);			
		}
	}
}
//функция читает один байт с устройства 1-wire
unsigned char w1_receive_byte(){
	unsigned char data;
	unsigned char i;
	for(i = 0; i < 8; i++)
	{	
		W1_DDR |= 1<<W1_BIT;
		_delay_us(2);
		W1_DDR &= ~(1<<W1_BIT) ;
		_delay_us(7);

		if((W1_PIN & (1<<W1_BIT)) == 0x00)
			data &= ~(1<<i);
		else
			data |= 1<<i;
		_delay_us(50);
	}
	return data;
}
//функция преобразует полученные с датчика 18b20 данные в температуру
int temp_18b20()
{
	unsigned char data[2];
	int temp = 0;
	if(w1_find()==1)//если есть устройство на шине
	{
		w1_sendcmd(0xcc);//пропустить ROM код, мы знаем, что у нас одно устройство или передаем всем
		w1_sendcmd(0x44);//преобразовать температуру
		_delay_ms(750);//преобразование в 12 битном режиме занимает 750ms
		w1_find();//снова посылаем Presence и Reset
		w1_sendcmd(0xcc);
		w1_sendcmd(0xbe);//передать байты ведущему(у 18b20 в первых двух содержится температура)
		data[0] = w1_receive_byte();//читаем два байта с температурой
		data[1] = w1_receive_byte();
			//загоняем в двух байтную переменную
		temp = data[1];
		temp = temp<<8;
		temp |= data[0];
		//переводим в градусы
		temp *= 0.0625;//0.0625 градуса на единицу данных
	}
	//возвращаем температуру
	return temp;
}