#ifndef __FUNCTIONS
#define __FUNCTIONS

#include <stdarg.h>
#include <stm32f1xx_hal_uart.h>

void UART_Printf(UART_HandleTypeDef * huart, const char* fmt, ...);

#endif //__FUNCTIONS