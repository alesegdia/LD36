#pragma once

#include <memory>

#include <enet/enet.h>

#include "protocol.h"

class Client
{
public:
	typedef std::shared_ptr<Client> SharedPtr;

	// CLIENT
	Client();

	~Client();

	bool isHostCreated();
	bool isPeerConnected();
	bool connect( const char* ip );
	void sendReady();
	bool hasGameStarted();

private:

	void createHost();

	ENetHost* m_host = nullptr;
	ENetPeer* m_peer = nullptr;
	uint8_t m_playerID = 0 ;

};
