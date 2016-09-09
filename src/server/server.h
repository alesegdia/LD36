#pragma once

#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <initializer_list>
#include <enet/enet.h>

#include "../core/network/protocol.h"

template <size_t Size>
class ByteBuffer
{
public:

	ByteBuffer( std::initializer_list<uint8_t> il )
	{
		assert(il.size() == Size);
		int i = 0;
		for( auto item : il )
		{
			m_data[i++] = item;
		}
	}

	ByteBuffer( uint8_t data[Size] )
	{
		memcpy( data, m_data, Size );
	}

	size_t size()
	{
		return Size;
	}

	uint8_t& operator[]( size_t index )
	{
		assert(index < Size);
		return m_data[index];
	}

	const uint8_t& operator[]( size_t index ) const
	{
		assert(index < Size);
		return m_data[index];
	}

	operator void* ()
	{
		return static_cast<void*>(m_data);
	}

	operator const void* () const
	{
		return static_cast<const void*>(m_data);
	}

	const void* data() const
	{
		return static_cast<const void*>(m_data);
	}

private:
	uint8_t m_data[Size];

};

template <size_t Size>
ENetPacket* sv_makepacket( const ByteBuffer<Size>& buffer )
{
	char data[2] = { 1, 2 };
	return enet_packet_create( buffer, Size, ENET_PACKET_FLAG_RELIABLE );
}

template <size_t Size>
void sv_send( ENetHost* host_, ENetPeer* peer, const ByteBuffer<Size>& buffer )
{
	ENetPacket* packet = sv_makepacket( buffer );
	enet_peer_send( peer, 0, packet );
	enet_host_flush(host_);
}

template <size_t Size>
void sv_broadcast( ENetHost* host, const ByteBuffer<Size>& buffer )
{
	ENetPacket* packet = sv_makepacket( buffer );
	enet_host_broadcast( host, 0, packet );
	enet_host_flush(host);
}

void sv_broadcast_startgame( ENetHost* host, uint8_t starter_player_id )
{
	sv_broadcast( host, ByteBuffer<2>{ uint8_t(PacketType::StartGame), starter_player_id } );
}

void sv_assign_id( ENetHost* host, ENetPeer* peer, uint8_t assigned_id )
{
	sv_send( host, peer, ByteBuffer<2>{ uint8_t(PacketType::AssignID), assigned_id } );
}


