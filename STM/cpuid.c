/* Includes ------------------------------------------------------------------*/
#include "cpuid.h"



volatile uint32_t CPU_UID = 0;
volatile uint8_t CPU_UID_ARRAY[4] = { 0x00, 0x00, 0x00, 0x00 };
static unsigned long *UID = (unsigned long *)0x1FFFF7E8;



void getCPUID(void)
{
	CPU_UID = UID[0] ^ UID[1] ^ UID[2] ^ UID[3];

	CPU_UID_ARRAY[0] = CPU_UID >> 24;
	CPU_UID_ARRAY[1] = CPU_UID >> 16;
	CPU_UID_ARRAY[2] = CPU_UID >> 8;
	CPU_UID_ARRAY[3] = CPU_UID;
}
