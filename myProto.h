#include "myDevicesIDs.h"

#define MYPROTO_BUFF_SIZE			32
#define MYPROTO_BUFF_MASK			MYPROTO_BUFF_SIZE - 1

uint8_t myproto_rx_buff[MYPROTO_BUFF_SIZE];
uint8_t myproto_rx_rIndx = 0;
uint8_t myproto_rx_wIndx = 0;

enum{
  MYPROTO_START_BYTE			= 0xA1,
  MYPROTO_STOP_BYTE				= 0x1A,

  MYPROTO_CMD_ERROR				= 0xFF,
  MYPROTO_CMD_ERROR_CRC			= 0xFE,
  
  MYPROTO_CMD_SUCCESS			= 0x00,
  MYPROTO_CMD_SET_ADDRESS		= 0x01,
  MYPROTO_CMD_READ_DATA,
};

struct MyProtoPkt{
	uint8_t cmd;
	uint8_t len;
	uint8_t data[MYPROTO_BUFF_SIZE];
	uint8_t crc;
	uint8_t processF;
	uint8_t readlen;
	struct Flags {
		unsigned valid			: 1;
		unsigned crcError		: 1;
	} flags;
} recvPkt;


void myproto_init()
{
	recvPkt.processF		= 0;
	recvPkt.readlen			= 0;
}

void myproto_setRXData( uint8_t* buff, const uint8_t *len )
{
	uint8_t i;
	for( i = 0; i < *len; i++ ){
		myproto_rx_buff[ myproto_rx_wIndx++ & MYPROTO_BUFF_MASK ] = buff[i];
	}
}

uint8_t myproto_packData( uint8_t* out_buff, const uint8_t cmd, uint8_t* data, const uint8_t len )
{
	uint8_t crc		= 0;
	uint8_t ch		= 0;
	uint8_t i;
	
	crc				+= cmd;
	crc				+= len;
	
	out_buff[ch++]	= MYPROTO_START_BYTE;
	out_buff[ch++]	= cmd;
	out_buff[ch++]	= len;
	for( i = 0; i < len; i++ ){
		out_buff[ch++] = data[i];
		crc += data[i];
	}
	out_buff[ch++]	= crc;
	out_buff[ch++]	= MYPROTO_STOP_BYTE;
	
	return ch;
}

void myproto_process()
{
	while( myproto_rx_wIndx != myproto_rx_wIndx ){
		uint8_t byte = myproto_rx_buff[ myproto_rx_wIndx++ & UART_BUFF_MASK ];
		
		if( !recvPkt.processF ){
			if( byte == MYPROTO_START_BYTE ){
				recvPkt.processF++;
			}
			continue;
		}
		
		switch( recvPkt.processF ){
			case 1:
				recvPkt.cmd = byte;
				recvPkt.processF++;
			break;
			case 2:
				recvPkt.len = byte;
				recvPkt.processF++;
				if( recvPkt.len == 0 ) recvPkt.processF++;
			break;
			case 3:
				if( recvPkt.readlen < recvPkt.len ){
					recvPkt.data[recvPkt.readlen++] = byte;
				}else{
					recvPkt.data[recvPkt.readlen] = 0x00;
					recvPkt.processF++;
				}
			break;
			case 4:
				recvPkt.crc = byte;
				recvPkt.processF++;
			break;
		}
		
		if( recvPkt.processF == 5 ){
			
			recvPkt.processF = 0;
			
			if( byte == MYPROTO_STOP_BYTE ){
				uint8_t i;
				uint8_t crc = 0;
				crc += recvPkt.cmd;
				crc += recvPkt.len;
				for( i = 0; i < recvPkt.len; i++ ){
					crc += recvPkt.data[i];
				}
				if( crc == recvPkt.crc ){
					recvPkt.flags.crcError = 0;
				}
				recvPkt.flags.valid = 1;
				break;
			}
			
			recvPkt.flags.valid = 0;
		}
	}
}
