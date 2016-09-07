#include "client.h"

#include <iostream>
#include <cstring>
Client::Client(const char *ip)
{
	m_host = enet_host_create( nullptr,
							   1,			// only allow 1 outgoing connection)
							   2,			// allow up 2 channels to be used, 0 and 1
							   57600 / 8,	// 56K modem with 56 Kbps downstream bandwidth
							   14400 / 8	// 56K modem with 14 Kbps upstream bandwidth
							   );

	ENetAddress address;
	enet_address_set_host(&address, ip);
	address.port = NetworkConfig::Port;
	m_peer = enet_host_connect( m_host, &address, 2, 1 );

	ENetEvent event;
	if (enet_host_service (m_host, & event, 5000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection to " << ip << ":" << NetworkConfig::Port << " succeeded." << std::endl;
		ENetPacket * packet = enet_packet_create ("packet",
												  strlen ("packet") + 1,
												  ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send( m_peer, 0, packet);
		enet_host_flush(m_host);
	}
	else
	{
		enet_peer_reset (m_peer);
		std::cout << "Connection to " << ip << ":" << NetworkConfig::Port << " failed." << std::endl;
	}
}

Client::~Client()
{
	if( nullptr != m_host )
	{
		ENetEvent event;
		enet_peer_disconnect(m_peer, 123);
		while( enet_host_service(m_host, &event, 5000) > 0 )
		{
			if( event.type == ENET_EVENT_TYPE_DISCONNECT )
			{
				break;
			}
		}
		enet_host_destroy(m_host);
	}
}

bool Client::isHostCreated()
{
	return nullptr != m_host;
}

bool Client::isPeerConnected()
{
	return nullptr != m_peer;
}

void Client::createHost()
{

}
