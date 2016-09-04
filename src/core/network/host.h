#pragma once

#include <enet/enet.h>

class Host
{
public:
	Host( bool is_server = false )
	{
		if( true == is_server )
		{
			ENetAddress address;
			address.host = ENET_HOST_ANY;
			address.port = 9834;
			m_host = enet_host_create( &address,	// the address to bind the server host to
									   32,			// allow up to 32 clients and/or outgoing connections
									   2,			// allow up to 2 channels to be used, 0 and 1
									   0,			// assume any amount of incoming bandwidth
									   0			// assume any amount of outgoing bandwidth
									   );
		}
		else
		{
			m_host = enet_host_create( nullptr,
									   1,			// only allow 1 outgoing connection)
									   2,			// allow up 2 channels to be used, 0 and 1
									   57600 / 8,	// 56K modem with 56 Kbps downstream bandwidth
									   14400 / 8	// 56K modem with 14 Kbps upstream bandwidth
									   );
		}
	}

	~Host()
	{
		if( nullptr != m_host )
		{
			enet_host_destroy(m_host);
		}
	}

	bool isValid()
	{
		return nullptr != m_host;
	}

private:
	ENetHost* m_host = nullptr;

};
