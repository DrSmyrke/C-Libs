#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Defines -------------------------------------------------------------------*/




/* Variables -----------------------------------------------------------------*/
#pragma pack(push, 1)
typedef struct {
	uint8_t *pBuffer;
	uint16_t wIndx;
	uint16_t rIndx;
	uint16_t size;
} RingBuffer;
#pragma pack(pop)



/* Functions -----------------------------------------------------------------*/
void RING_BUFFER_init(RingBuffer *buffer, const uint8_t *buff, const uint16_t size);
uint16_t RING_BUFFER_available(const RingBuffer *buffer);
uint8_t RING_BUFFER_read(RingBuffer *buffer);
void RING_BUFFER_clear(RingBuffer *buffer);
void RING_BUFFER_write(RingBuffer *buffer, const uint8_t value);




#ifdef __cplusplus
}
#endif

#endif /* __RING_BUFFER_H__ */
