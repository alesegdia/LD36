
#include "packetbuilder.h"

ENetPacket *create_enet_packet(Buffer::Ptr buffer)
{
	return enet_packet_create( buffer->data(), buffer->size(), ENET_PACKET_FLAG_RELIABLE );
}
