
#include "utils.h"

Host::SharedPtr netutils_create_host_from_args(int argc, char **argv)
{
	Host::SharedPtr host = nullptr;

	if( argc != 2 )
	{
		printf("Usage: \t./game <server-ip> <port>\n");
		return nullptr;
	}

	const char* server_ip = argv[1];
	printf("connecting to %s\n", server_ip);
	host = std::make_shared<Host>(server_ip);

	return host;
}

