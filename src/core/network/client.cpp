#include "client.h"

#include <iostream>
#include <cstring>
Client::Client()
{
	m_host = enet_host_create( nullptr,
							   1,			// only allow 1 outgoing connection)
							   2,			// allow up 2 channels to be used, 0 and 1
							   57600 / 8,	// 56K modem with 56 Kbps downstream bandwidth
							   14400 / 8	// 56K modem with 14 Kbps upstream bandwidth
							   );

}

Client::~Client()
{
	if( nullptr != m_host )
	{
		ENetEvent event;
		if( m_peer != nullptr )
		{
			enet_peer_disconnect(m_peer, 123);
			while( enet_host_service(m_host, &event, 5000) > 0 )
			{
				if( event.type == ENET_EVENT_TYPE_DISCONNECT )
				{
					break;
				}
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

bool Client::connect(const char *ip)
{
	ENetAddress address;
	enet_address_set_host(&address, ip);
	address.port = NetworkConfig::Port;
	m_peer = enet_host_connect( m_host, &address, 2, 1 );

	ENetEvent event;
	if (enet_host_service (m_host, & event, 1000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection to " << ip << ":" << NetworkConfig::Port << " succeeded." << std::endl;

		if( enet_host_service( m_host, &event, 1000 ) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE )
		{
			std::cout << "Assigned ID: " << int(event.packet->data[1]) << std::endl;
			m_playerID = event.packet->data[1];
		}
		else
		{
			std::cout << "ID assignation not working" << std::endl;
			return false;
		}
	}
	else
	{
		enet_peer_reset (m_peer);
		std::cout << "Connection to " << ip << ":" << NetworkConfig::Port << " failed." << std::endl;
		return false;
	}
	return true;
}

void Client::sendReady()
{
	uint8_t data[2] = { uint8_t(PacketType::Ready), m_playerID };
	ENetPacket* packet = enet_packet_create(data, 2, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send( m_peer, 0, packet );
	enet_host_flush( m_host );
}

bool Client::hasGameStarted()
{
	ENetEvent event;
	if( enet_host_service( m_host, &event, 0 ) && event.type == ENET_EVENT_TYPE_RECEIVE )
	{
		return true;
	}
	return false;
}

void Client::createHost()
{

}
