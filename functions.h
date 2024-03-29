#ifndef _MAIN_FUNCTIONS_H_
#define _MAIN_FUNCTIONS_H_


#include <stdint.h>
#include <support_defines.h>


uint8_t pack_string( uint8_t* buff, const char* string )
{
	uint8_t len = 0;
	while(*string != '\0'){
		buff[len++] = (uint8_t)*string;
		string++;
	}
	return len;
}

void delay(uint16_t t){
	uint16_t x;
	for (x=t;x>0;x--) asm("nop"); 
}

void delay2(void)
{
	uint8_t i;
	uint16_t i2;
	for(i = 0; i < 16; i++){
		for(i2 = 0; i2 < 65000; i2++) asm("nop");
	}
}
void delay3(void)
{
	uint8_t i;
	uint16_t i2;
	for(i = 0; i < 8; i++){
		for(i2 = 0; i2 < 65000; i2++) asm("nop");
	}
}
void delay4(void)
{
	uint8_t i;
	uint16_t i2;
	for(i = 0; i < 4; i++){
		for(i2 = 0; i2 < 65000; i2++) asm("nop");
	}
}

uint8_t symToHex(uint8_t i)
{
  uint8_t res;
  if( (i>('0'-1) && i<('9'+1)) || (i>('A'-1) && i<('Z'+1)) )
  {
    if(i<('9'+1)) res=(i-'0');
    else res=(i-'A'+10);
  }
  return res;
}

uint8_t strToUChar( uint8_t *str, const uint8_t len )
{
	uint8_t val = 0;
	uint8_t i;
	
	for( i = 0; i < len; i++ ){
		if( str[i] == '.' || str[i] == '\0' ) break;
		if( str[i] == '-' || str[i] > 0x39 ) continue;
		val *= 10;
		val += symToHex( str[i] );
	}
	return val;
}

int16_t strToShort2( uint8_t *str )
{
	int16_t val = 0;
	uint8_t minus = false;

	while(*str != '\0'){
		if( *str == '.' ) break;
		if( *str == '-' ) minus = true;
		if( *str == '-' || *str > 0x39 ) continue;
		val *= 10;
		val += symToHex( *str );
		str++;
	}
	if( minus ) val = 0 - val;
	return val;
}

uint8_t strToDrob( uint8_t *str )
{
	uint8_t val = 0;
	uint8_t find = false;

	while(*str != '\0'){
		if( find ) val = symToHex( *str );
		if( *str == '.' ) find = true;
		if( *str == '-' || *str > 0x39 ) continue;		
		str++;
	}
	return val;
}


/*
void strToUInt( uint8_t *str, const uint8_t len, void *val, uint8_t *valDrob )
{
	*val = 0;
	*valDrob = 0;

	uint8_t drob = false;
	uint8_t i;

	for( i = 0; i < len; i++ ){
		if( str[i] == '-' || str[i] > 0x39 ) continue;
		if( str[i] == '.' ){
			drob = true;
			continue;
		}
		if( drob ){
			*valDrob = symToHex( str[i] );
			break;
		}
		*val *= 10;
		*val += symToHex( str[i] );
	}
}

void strToInt( uint8_t *str, const uint8_t len, int32_t val, uint8_t valDrob )
{
	val = 0;
	valDrob = 0;

	uint8_t minusF = false;
	uint8_t drob = false;
	uint8_t i;

	for( i = 0; i < len; i++ ){
		if( str[i] > 0x39 ) continue;
		if( str[i] == '-' ){
			minusF = true;
			continue;
		}
		if( str[i] == '.' ){
			drob = true;
			continue;
		}
		if( drob ){
			valDrob = symToHex( str[i] );
			break;
		}
		val *= 10;
		val += symToHex( str[i] );
	}
	if( minusF ) val = 0 - val;
}
*/

#endif //_MAIN_FUNCTIONS_H_
