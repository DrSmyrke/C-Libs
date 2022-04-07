#ifndef MINICONF_H
#define MINICONF_H

#ifdef __cplusplus
#include <iostream>
#endif

void miniconf_parsFile( const char *filename );
void miniconf_setParam( const char *param, const char *value );
uint8_t miniconf_count( const char* data );
void miniconf_saveInit( const char *filename );
void miniconf_saveParam( const char *param, const char *value );
void miniconf_saveParam( const char *param, uint8_t value );
void miniconf_saveEnd();
void miniconf_reverseArray(char *array );
char* miniconf_itoa( uint32_t value );

#endif // MINICONF_H
