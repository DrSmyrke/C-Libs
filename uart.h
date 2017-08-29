#define BAUDRATE 9600 // Скорость обмена данными
#include <string.h>
#include <avr/interrupt.h> 
void uart_init(){
// Параметры соединения: 8 бит данные, 1 стоповый бит, нет контроля четности
// USART Приемник: Включен
// USART Передатчик: Включен
// USART Режим: Асинхронный
// USART Скорость обмена: 9600
    //UCSRA=0x00;
    UCSRB=0x18;
	UCSRC=0x86;
	UBRRH=0x00;
    UBRRL=0x33;
	UCSRB=( 1 << TXEN ) | ( 1 << RXEN ) | (1 << RXCIE );
	UCSRC |= (1 << URSEL)| // Для доступа к регистру UCSRC выставляем бит URSEL
	(1 << UCSZ1)|(1 << UCSZ0); // Размер посылки в кадре 8 бит
}
// Прерывание по окончанию приема данных по USART
ISR(USART_RXC_vect){
	//UART_Transmit(0x00);
	//delay(100);
	//UART_Transmit(tc);
}
// Функция передачи данных по USART
void uart_send(char data){
	while(!( UCSRA & (1 << UDRE)));   // Ожидаем когда очистится буфер передачи
	UDR = data; // Помещаем данные в буфер, начинаем передачу
}
 // Функция передачи строки по USART
void str_uart_send(char *string){
	while(*string != '\0'){
		uart_send(*string);
		string++;
	}
}
