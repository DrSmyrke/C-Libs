#define ONEWIRE_PROGRAMMER_TYPE			0x11


enum{
	MYPROTO_START_BYTE				= 0xA1,
	MYPROTO_STOP_BYTE					= 0x1A,

	MYPROTO_CMD_ERROR					= 0xFF,
	MYPROTO_CMD_ERROR_CRC				= 0xFE,
  
	MYPROTO_CMD_SUCCESS				= 0x00,
	MYPROTO_CMD_GET_ID,
	MYPROTO_CMD_SCAN,
	MYPROTO_CMD_READ,
	MYPROTO_CMD_SEND,
	MYPROTO_CMD_SEND_READ,			// 0x05
	MYPROTO_CMD_SET_ADDRESS,			
};