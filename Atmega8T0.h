#ifndef _ATMEGA8_T0_H_
#define _ATMEGA8_T0_H_

#include <stdint.h>

extern uint8_t ms100Flag;
extern uint8_t secondFlag;


void t0_reset(void);
void t0_init(void);


#endif // _ATMEGA8_T0_H_
