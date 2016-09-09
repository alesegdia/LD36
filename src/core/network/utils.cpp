
#include "utils.h"

Client::SharedPtr netutils_create_host_from_args(int argc, char **argv)
{
	Client::SharedPtr host = nullptr;

	if( argc != 2 )
	{
		printf("Usage: \t./game <server-ip> <port>\n");
		return nullptr;
	}

	const char* server_ip = argv[1];
	host = std::make_shared<Client>();
	host->connect(server_ip);

	return host;
}

