#include <enet/enet.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <initializer_list>
#include <algorithm>
#include <signal.h>

#include "server.h"

static uint8_t last_player_id = 0 ;
static ENetAddress address;
static ENetHost* host;
static ENetEvent event;
static ServerState state = ServerState::AwaitingConnections;
static uint32_t players_ready[NetworkConfig::NumClients];

// ask at enet: 1) no need to destroy sent package?
//				2) can't remember right now

int main( int argc, char** argv )
{
	memset( players_ready, 0, NetworkConfig::NumClients );

	if( enet_initialize() != 0 )
	{
		std::cerr << "Couldn't initialize enet" << std::endl;
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);

	std::cout << "Open at port " << NetworkConfig::Port << std::endl;

	enet_address_set_host(&address, "127.0.0.1");
	address.port = NetworkConfig::Port;

	host = enet_host_create( &address,	// the address to bind the server host to
							 NetworkConfig::NumClients,
										// allow up to 32 clients and/or outgoing connections
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
		if( state == ServerState::AwaitingConnections )
		{
			bool all_ready = true;
			for( int i = 1; i <= std::max(uint8_t(2), last_player_id); i++ )
			{
				if( players_ready[i] == false )
				{
					all_ready = false;
					break;
				}
			}

			if( all_ready )
			{
				std::cout << "All ready... Starting game!" << std::endl;
				state = ServerState::Game;
				sv_broadcast_startgame( host, 1 );
			}
		}

		while( enet_host_service( host, &event, 0 ) > 0 )
		{
			if( state == ServerState::AwaitingConnections )
			{
				switch( event.type )
				{
				case ENET_EVENT_TYPE_CONNECT:
					char ip[16];
					enet_address_get_host_ip(&event.peer->address, ip, 16);
					std::cout << "New connection from " << ip << std::endl;
					sv_assign_id( host, event.peer, ++last_player_id );
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					if( uint8_t(PacketType::Ready) == event.packet->data[0] )
					{
						assert( event.packet->dataLength == 2 );
						size_t player_id = event.packet->data[1];
						players_ready[player_id] = !players_ready[player_id];
						std::cout << "Player " << int(player_id) << " ready." << std::endl;
					}
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << event.peer->data << " disconnected." << std::endl;
					event.peer->data = NULL;
					break;

				case ENET_EVENT_TYPE_NONE:
					std::cout << "Unhandled event " << event.type << std::endl;
					break;

				}
			}
			else if( state == ServerState::Game )
			{
				switch( event.type )
				{
				case ENET_EVENT_TYPE_RECEIVE:
					std::cout << "Msg: " << event.packet->data << std::endl;
					enet_host_broadcast(host, 0, event.packet);
					enet_host_flush(host);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << event.peer->data << " disconnected." << std::endl;
					event.peer->data = NULL;
					break;

				case ENET_EVENT_TYPE_CONNECT:
				case ENET_EVENT_TYPE_NONE:
					std::cout << "Unhandled event " << event.type << std::endl;
					break;
				}
			}
		}
	}

	enet_host_destroy(host);
	return 0;
}
