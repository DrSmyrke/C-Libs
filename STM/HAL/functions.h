#ifdef __ARMCC_VERSION

#ifndef __FUNCTIONS
#define __FUNCTIONS

#include <stdarg.h>

void UART_Printf(UART_HandleTypeDef * huart, const char* fmt, ...);



#endif //__FUNCTIONS
#endif //__ARMCC_VERSION
