#ifdef _UNCOMPLETED_H

#include "miniconf.h"

int main()
{
	miniconf_parsFile( "settings.cfg" );

	miniconf_saveInit( "settings2.cfg" );
	miniconf_saveParam( "firstParam", "20" );
	miniconf_saveParam( "nextParam", "testVal" );
	miniconf_saveParam( "newParam", 137 );
	miniconf_saveParam( "lastParam", "\"Value\"" );
	miniconf_saveEnd();

    return 0;
}


#endif /* _UNCOMPLETED_H */
