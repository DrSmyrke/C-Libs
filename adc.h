#ifndef _MAIN_ADC_H_
#define _MAIN_ADC_H_

#include <avr/interrupt.h>
#include <avr/io.h>



//--- VARIABLES -----------------------------------------------------------------------------
extern uint16_t vcc3;
extern uint16_t vcc5;
extern uint8_t adc_intFlag;

//--- FUNCTIONS -----------------------------------------------------------------------------
void adc_init(void);
void adc_readData(void);
void adc_run(void);
uint8_t adc_isLight(void);


#endif // _MAIN_ADC_H_
