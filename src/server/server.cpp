#include <enet/enet.h>
#include <iostream>

int main( int argc, char** argv )
{
	ENetAddress address;
	ENetHost* host;
	ENetEvent event;

	if( enet_initialize() != 0 )
	{
		std::cerr << "Couldn't initialize enet" << std::endl;
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);

	address.host = ENET_HOST_ANY;
	address.port = 4943;

	host = enet_host_create( &address,	// the address to bind the server host to
							 32,		// allow up to 32 clients and/or outgoing connections
							 2,			// allow up to 2 channels to be used, 0 and 1
							 0,			// assume any amount of incoming bandwidth
							 0			// assume any amount of outgoing bandwidth
							 );

	if( host == nullptr )
	{
		std::cerr << "Error creating enet host" << std::endl;
		exit(EXIT_FAILURE);
	}

	while( true )
	{
		while( enet_host_service( host, &event, 1000 ) > 0 )
		{
			switch( event.type )
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "New connection from "
					<< std::hex << event.peer->address.host << std::endl;
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Msg: " << event.packet->data << std::endl;
				enet_host_broadcast(host, 0, event.packet);
				enet_host_flush(host);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << event.peer->data << " disconnected." << std::endl;
				event.peer->data = NULL;
				break;
			}
		}
	}

	enet_host_destroy(host);
	return 0;
}
