#include <iostream>
#include <cstring>

#include "common.h"

int main( int argc, char** argv )
{
	if( enet_initialize() != 0 )
	{
		return -1;
	}
	atexit( enet_deinitialize );

	if( argc <= 2 )
	{
		return 1;
	}
	if( argc == 1 && strcmp(argv[0], "1") != 0 )
	{
		//fprintf(stderr, "Connected")
		return 1;
	}
	return 0;

}
