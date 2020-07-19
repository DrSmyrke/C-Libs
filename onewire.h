#include <avr/io.h>

#ifdef ONWIRE_RAM_CRC
	#include <avr/pgmspace.h>
#endif

#include <util/delay.h>

#define ONEWIRE_PORT		PORTB
#define ONEWIRE_DDR			DDRB
#define ONEWIRE_PIN			PINB
#define ONEWIRE_PIN_NUM		0


uint8_t onewire_enum[9];
uint8_t onewire_enum_fork_bit;


#ifdef ONWIRE_RAM_CRC
const uint8_t PROGMEM onewire_crc_table[] = {
	0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41, 
	0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc, 
	0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62, 
	0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff, 
	0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07, 
	0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a, 
	0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24, 
	0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9, 
	0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd, 
	0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50, 
	0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee, 
	0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73, 
	0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b, 
	0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16, 
	0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8, 
	0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35  
};
#endif

inline void onewire_low()
{
	setPlus(ONEWIRE_DDR,ONEWIRE_PIN_NUM);
}

inline void onewire_high()
{
	setZero(ONEWIRE_DDR,ONEWIRE_PIN_NUM);
}

inline uint8_t onewire_getBit()
{
	return CheckBit(ONEWIRE_PIN,ONEWIRE_PIN_NUM);
}

inline uint8_t onewire_check_crc()
{
	return ( onewire_enum[8] == 0x00 ) ? 0x01 : 0x00;
}

inline uint8_t onewire_getFamilyCode()
{
	return onewire_enum[0];
}

inline uint8_t onewire_getCode( const uint8_t num )
{
	return ( num > 8 ) ? 0xFF : onewire_enum[ num ];
}

void onewire_master_init()
{
	ONEWIRE_PORT &= ~_BV(ONEWIRE_PIN_NUM);
	onewire_high();
}

/*
	@description Send signal RESET
	@return 1 if recieve impulse else 0
*/
uint8_t onewire_reset() 
{
	onewire_low();
	_delay_us(640);		// Delay 480..960 mcs
	onewire_high();
	_delay_us(2);
	// Delay >= 60 mcs
	uint8_t i;
	for( i = 80; i > 0; i-- ){
		if( !onewire_getBit() ){
			// If recieve welcome signal, wait end
			while( !onewire_getBit() );
			return 1;
		}
		_delay_us(1);
	}
	return 0;
}

//send bit
void onewire_send_bit( const uint8_t bit )
{
	onewire_low();
	if( bit ){
		_delay_us(5);	// Delay 1..15 mcs
		onewire_high();
		_delay_us(90);	// Delay >= 60 mcs
	}else{
		_delay_us(90);	// Delay 60..120 mcs
		onewire_high();
		_delay_us(5);
	}
}

//send byte
void onewire_send( const uint8_t byte )
{
	uint8_t i;
	for( i = 0; i < 8; i++ ){
		onewire_send_bit( CheckBit(byte,i) );
	}
}

//read bit
uint8_t onewire_read_bit()
{
	onewire_low();
	_delay_us(2);	// Delay >= 1 mcs
	onewire_high();
	_delay_us(8);	// Delay < 15 mcs
	uint8_t r = onewire_getBit();
	_delay_us(80);	// Delay >= 60 mcs
	return r;
}

//read byte
uint8_t onewire_read()
{
	uint8_t res = 0;
	uint8_t i;
	for( i = 0; i < 8; i++ ){
		if( onewire_read_bit() ){
			setPlus(res,i);
		}else{
			setZero(res,i);
		}
	}
	return res;
}

//return crc update value
uint8_t onewire_crc_update( uint8_t crc, uint8_t byte )
{
#ifdef ONWIRE_RAM_CRC
	return pgm_read_byte(&onewire_crc_table[crc ^ b]);
#else	
	uint8_t i;
	while( i++ < 8 ){
		crc = ((crc ^ byte) & 1) ? (crc >> 1) ^ 0b10001100 : (crc >> 1);
		byte >>= 1;
	}
	return crc;
	#endif
}

//////////////////////////////////////////////////////////
//					ROM COMMANDS						//
//////////////////////////////////////////////////////////
/*
	@description Exec init process (reset+wait welcome impulse), if recieve impulse send command SKIP ROM
	@return 1 if recieve impulse else 0
*/
uint8_t onewire_rom_skip()
{
	if( !onewire_reset() ) return 0;
	onewire_send( 0xCC );
	return 1;
}

/*
	@description Exec init process (reset+wait welcome impulse), if recieve impulse send command READ ROM and read 8 byte code
	@return 1 if recieve impulse else 0
*/
uint8_t onewire_rom_read(uint8_t * buf)
{
	if (!onewire_reset()) return 0; 
	onewire_send(0x33);
	uint8_t p;
	for (p = 0; p < 8; p++) {
		*(buf++) = onewire_read();
	}
	return 1;
}

/*
	@description Exec init process (reset+wait welcome impulse), if recieve impulse send command MATCH ROM and 8 byte code
	@return 1 if recieve impulse else 0
*/
uint8_t onewire_rom_match( const uint8_t* data )
{
	if( !onewire_reset() ) return 0;
	onewire_send( 0x55 );
	uint8_t i;
	for( i = 0; i < 8; i++ ){
		onewire_send( *(data++) );
	}
	return 1;
}

//////////////////////////////////////////////////////////
//					            						//
//////////////////////////////////////////////////////////

uint8_t onewire_isBroadcast( const uint8_t* addr )
{
	uint8_t res = 1;
	
	uint8_t i;
	for( i = 0; i < 8; i++ ){
		if( *(addr++) != 0x00 ){
			res = 0;
			break;
		}
	}
	
	return res;
}

/*
	@description Start initialize finding devices
	@return 
*/
void onewire_enum_init()
{
	uint8_t i;
	for( i = 0; i < 8; i++ ){
		onewire_enum[i] = 0;
	}   
	onewire_enum_fork_bit = 65;
}

/*
	@description Enumerates the device on the 1-wire bus and receives the next address.
	@return pint of buffer address device
*/
uint8_t onewire_enum_next()
{
	//If there were no disagreements at the previous step, then we simply exit without returning anything.
	if( !onewire_enum_fork_bit ){
		return 0;
	}
	if( !onewire_reset() ){
		return 0;
	}
	
	uint8_t bitNum = 8;
	uint8_t * pprev = &onewire_enum[0];
	uint8_t prev = *pprev;
	uint8_t next = 0;
  
	uint8_t p = 1;
	onewire_send(0xF0);	//SEND FIND ROM COMMAND
  
	uint8_t newfork = 0;
	for(;;){
		uint8_t bit1 = onewire_read_bit();
		uint8_t bit2 = onewire_read_bit();
		//If bit zero is present in the addresses
		if( !bit1 ){
			//If bit one is present in the addresses (ERROR)
			if( !bit2 ){
				// If we are to the left of the past right conflict bit, 
				if( p < onewire_enum_fork_bit ){
					if( prev & 1 ){
						next |= 0x80; // then we copy the bit value from the last pass
					}else{
						newfork = p; // if zero, then remember the conflict place
					}          
				} else if ( p == onewire_enum_fork_bit ){
					next |= 0x80; // if last time there was a right-hand conflict with zero at this place, output 1
				}else{
					newfork = p; // to the right - we pass zero and remember the conflict place
				}        
			}
			// otherwise, we go, choosing zero in the address
		}else{
			// if 1
			if(! bit2 ){
				next |= 0x80;
			}else{
				//eror situation
				return 0;
			}
		}
		
		onewire_send_bit(next & 0x80);
		bitNum--;
		if( !bitNum ){
			*pprev = next;
			if (p >= 64) break;
			next = 0;
			pprev++;
			prev = *pprev;
			bitNum = 8;
		}else{
			if (p >= 64) break;
			prev >>= 1;
			next >>= 1;
		}
		p++;
	}
	
	onewire_enum_fork_bit = newfork;
	
	//Calculate CRC
	uint8_t crc = 0;
	uint8_t i;
	for( i = 0; i < 8; i++ ) {
		crc = onewire_crc_update( crc, onewire_enum[i] );
	}
	onewire_enum[8] = crc;
  
	return 1;
}
