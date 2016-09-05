#pragma once

#include <memory>

#include <enet/enet.h>

class Host
{
public:
	typedef std::shared_ptr<Host> SharedPtr;

	// CLIENT
	Host( const char* ip )
	{
		m_host = enet_host_create( nullptr,
								   1,			// only allow 1 outgoing connection)
								   2,			// allow up 2 channels to be used, 0 and 1
								   57600 / 8,	// 56K modem with 56 Kbps downstream bandwidth
								   14400 / 8	// 56K modem with 14 Kbps upstream bandwidth
								   );
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
