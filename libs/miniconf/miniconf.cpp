#include "miniconf.h"

FILE* file;
char buff[16];

void miniconf_parsFile( const char *filename )
{
	//TODO: проверка на существование файла
	FILE* f = fopen( filename, "rb" );
	char sym;
	char param[16];
	char value[32];
	uint8_t i = 0;
	bool paramF = false;
	bool commentF = false;

	if ( f ) {
		while( fread( &sym, 1, 1, f ) > 0 ){
			if( sym == '\t' || sym == '\r' ) continue;
			if( sym == '\n' ){
				value[i] = '\0';
				if( miniconf_count(param) > 0 && miniconf_count(value) > 0 ) miniconf_setParam( param, value );
				param[0] = '\0';
				value[0] = '\0';
				commentF = false;
				paramF = false;
				i = 0;
				continue;
			}
			if( commentF ) continue;
			if( !paramF ){
				if( i == 0 && sym == '#' ){
					commentF = true;
					continue;
				}
				if( sym == ' ' || sym == '=' ){
					param[i] = '\0';
					paramF = true;
					i = 0;
					continue;
				}
				param[i++] = sym;
			}else{
				if( i == 0 && sym == ' ' ) continue;
				if( i == 0 && sym == '=' ) continue;
				value[i++] = sym;
			}
		}

		fclose(f);
	}
}

uint8_t miniconf_count(const char *data)
{
	uint8_t i = 0;

	while( data[i++] != '\0' );

	return --i;
}

void miniconf_setParam(const char *param, const char *value)
{
	printf("[%s]=>[%s]\n",param,value);
}

void miniconf_saveInit(const char *filename)
{
	file = fopen( filename, "wb" );
	if ( !file ) return;
}

void miniconf_saveParam(const char *param, const char *value)
{
	if ( !file ) return;
	fwrite( param, miniconf_count(param), 1, file );
	fwrite( "=", 1, 1, file );
	fwrite( value, miniconf_count(value), 1, file );
	fwrite( "\n", 1, 1, file );
}

void miniconf_saveParam(const char *param, uint8_t value)
{
	if ( !file ) return;

	char *val = miniconf_itoa( value );

	miniconf_saveParam( param, val );
}

void miniconf_saveEnd()
{
	fclose( file );
}
char *miniconf_itoa( uint32_t value )
{
	uint8_t i = 0;

	while( value > 0 ){
		buff[i++] = ( value % 10 ) + '0';
		value /= 10;
	}

	buff[i] = '\0';
	miniconf_reverseArray(buff);

	return buff;
}

void miniconf_reverseArray(char *array)
{
	uint8_t size = miniconf_count( array );
	uint8_t i;
	char temp;

	for( i = 0; i < size / 2; i++ ){
		temp = array[size - i - 1];
		array[size - i - 1] = array[i];
		array[i] = temp;
	}
}
