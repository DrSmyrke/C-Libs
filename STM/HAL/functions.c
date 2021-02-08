#include "functions.h"

void UART_Printf(UART_HandleTypeDef * huart, const char* fmt, ...)
{
    char buff[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_UART_Transmit(huart, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY);
    va_end(args);
}
