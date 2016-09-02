#pragma once

#include <enet/enet.h>

class Networking
{
public:
	Networking()
	{
		m_status = enet_initialize();
	}

	~Networking()
	{
		if( m_status == 0 )
		{
			enet_deinitialize();
		}
	}

	int status()
	{
		return m_status;
	}

private:
	int m_status;

};
