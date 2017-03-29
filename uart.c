#define BAUD 9600
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
ISR(USART_RXC_vect ){	// прием данных
	//lcd_goto_xy(1,6);
	//itoa(ch,str,10);
	//lcd_str("PRIEM");
	//lcd_str(str);
}
ISR(USART_TXC_vect ){	// Отправка данных
	//lcd_goto_xy(1,2);
	//itoa(ch,str,10);
	//lcd_str("PERED");
	//lcd_str(str);
}
void uart_init(){
    UCSRA=0x00;
    UCSRB=0x18;
    UCSRC=0x86;
    UBRRH=0x00;
    UBRRL=0x33;
	//разрешить прием, передачу данных и прерывание по приёму байта
	UCSRB=( 1 << TXEN ) | ( 1 << RXEN ) | (1 << RXCIE ) | (1 << TXCIE );
}

void UART_Transmit(unsigned char data){
    while ( !( UCSRA & (1<<UDRE)) );
    UDR = data;
}

unsigned char UART_Receive(void) {
    while(!(UCSRA & (1<<RXC)) );
    return UDR;
}
void UART_STRING_Transmit(char *string){
	while(*string != '\0'){
		UART_Transmit(*string);
		string++;
	}
}
