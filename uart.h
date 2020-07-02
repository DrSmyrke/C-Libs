#define BAUDRATE 9600 // Скорость обмена данными

#include <string.h>
#include <avr/interrupt.h>

#define UART_BUFF_SIZE			32
#define UART_BUFF_MASK			UART_BUFF_SIZE - 1

uint8_t uart_rx_buff[UART_BUFF_SIZE];
uint8_t uart_rx_rIndx = 0;
uint8_t uart_rx_wIndx = 0;

void uart_init(){
	//Параметры соединения: 8 бит данные, 1 стоповый бит, нет контроля четности
	//USART Приемник: Включен
	//USART Передатчик: Включен
	//USART Режим: Асинхронный
	//USART Скорость обмена: 9600
    //UCSRA=0x00;
    UCSRB=0x18;
	UCSRC=0x86;
	UBRRH=0x00;
    UBRRL=0x33;

	UCSRB=( 1 << TXEN ) | ( 1 << RXEN ) | (1 << RXCIE );
	UCSRC |= (1 << URSEL)| // Для доступа к регистру UCSRC выставляем бит URSEL
	(1 << UCSZ1)|(1 << UCSZ0); // Размер посылки в кадре 8 бит
}

// Функция передачи данных по USART
void uart_send(uint8_t data)
{
	while(!( UCSRA & (1 << UDRE)));   // Ожидаем когда очистится буфер передачи
	UDR = data; // Помещаем данные в буфер, начинаем передачу
}

 // Функция передачи строки по USART
void str_uart_send(char *string)
{
	while(*string != '\0'){
		uart_send(*string);
		string++;
	}
}

void uart_send_buff( uint8_t* buff, const uint8_t len )
{
	uint8_t i;
	for( i = 0; i < len; i++ ){
		uart_send( buff[i] );
	}
}

uint8_t uart_receive(void) {
    while(!(UCSRA & (1<<RXC)) );
    return UDR;
}

uint8_t uart_isReadAvailable()
{
	return ( uart_rx_wIndx != uart_rx_rIndx ) ? 0x01 : 0x00;
}

uint8_t uart_readData(uint8_t* buff)
{
	uint8_t ch = 0;
	
	while( uart_rx_wIndx != uart_rx_rIndx ){
		buff[ch++] = uart_rx_buff[ uart_rx_rIndx++ & UART_BUFF_MASK ];
	}
	
	buff[ch] = 0x00;
	
	return ch;
}

// Прерывание по окончанию приема данных по USART
ISR(USART_RXC_vect)
{
	//uint8_t sym = uart_receive();
	uart_rx_buff[ uart_rx_wIndx++ & UART_BUFF_MASK ] = uart_receive();
}
// Отправка данных
ISR(USART_TXC_vect )
{

}
