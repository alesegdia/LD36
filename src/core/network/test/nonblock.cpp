#include <iostream>
#include <cstring>

#include "../utils.h"
#include "common.h"


int main( int argc, char** argv )
{
	if( enet_initialize() != 0 )
	{
		fprintf(stderr, "Couldn't load enet\n");
		return -1;
	}
	atexit(enet_deinitialize);

	Host::SharedPtr host = netutils_create_host_from_args( argc, argv );
	if( nullptr == host )
	{
		return -1;
	}

	return 0;
}
