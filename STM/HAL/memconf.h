#ifndef __MEMCONF_H__
#define __MEMCONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal_flash.h"



//#define FLASH_PAGE_SIZE					((uint16_t)0x400)
#define BANK1_WRITE_START_ADDR			((uint32_t)0x0801FC00)// 0x0803FC00 ~ 264k  //0x08008000 ((uint32_t))0x080FF000
#define BANK1_WRITE_END_ADDR			((uint32_t)0x08020000)// 0x08040000 ~ 265k //   0x08008400 ((uint32_t))0x080FF400
//#define MAX_SETTINGS_PARAMS             FLASH_PAGE_SIZE/4
#define MAX_SETTINGS_PARAMS             79



enum{
	settings_param_nrd_uid				= 0,
	settings_param_time_move_m			= 74,
	settings_param_resh_sleep,
	settings_param_ip					= 78,
};



extern volatile uint32_t memory_conf[ MAX_SETTINGS_PARAMS ];


void READ_MEMORY_SETTINGS(void);
void SAVE_MEMORY_SETTINGS(void);
void SAVE_MEMORY_PARAM(const uint8_t paramID, const uint32_t value);



#ifdef __cplusplus
}
#endif

#endif /* __MEMCONF_H__ */
