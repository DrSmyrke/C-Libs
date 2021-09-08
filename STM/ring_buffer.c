/* Includes ------------------------------------------------------------------*/
#include "ring_buffer.h"



/* Variables -----------------------------------------------------------------*/




/* Functions -----------------------------------------------------------------*/
void RING_BUFFER_init(RingBuffer *buffer, const uint16_t size)
{
	uint8_t buff[ size ];
	
	buffer->pBuffer		= buff;
	buffer->size		= size;
	
	RING_BUFFER_clear( buffer );
}

uint16_t RING_BUFFER_available(const RingBuffer *buffer)
{
	return ((uint16_t)(buffer->size + buffer->wIndx - buffer->rIndx)) % buffer->size;
}

uint8_t RING_BUFFER_read(RingBuffer *buffer)
{
	if( buffer->wIndx == buffer->rIndx ){
		return 0;
	}else{
		uint8_t byte = buffer->pBuffer[ buffer->rIndx ];
		buffer->rIndx = (uint16_t)(buffer->rIndx + 1) % buffer->size;
		return byte;
	}
}

void RING_BUFFER_clear(RingBuffer *buffer)
{
	buffer->rIndx = 0;
	buffer->wIndx = 0;

	for( uint16_t i = 0; i < buffer->size; i++ ){
		buffer->pBuffer[ i ] = '\0';
	}
}

void RING_BUFFER_write(RingBuffer *buffer, const uint8_t value)
{
	buffer->pBuffer[ buffer->wIndx ];
	buffer->wIndx = (uint16_t)(buffer->wIndx + 1) % buffer->size;
}
