#ifndef __CPUID_H__
#define __CPUID_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/



extern volatile uint32_t CPU_UID;
extern volatile uint8_t CPU_UID_ARRAY[4];



void getCPUID(void);



#ifdef __cplusplus
}
#endif

#endif /* __CPUID_H__ */
