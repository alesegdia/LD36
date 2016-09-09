#pragma once

#include <memory>

#include <enet/enet.h>

#include "protocol.h"

class Client
{
public:
	typedef std::shared_ptr<Client> SharedPtr;

	// CLIENT
	Client( const char* ip );

	~Client();

	bool isHostCreated();

	bool isPeerConnected();

private:

	void createHost();

	ENetHost* m_host = nullptr;
	ENetPeer* m_peer = nullptr;

};
