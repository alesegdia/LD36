#pragma once

#include <enet/enet.h>

#include "buffer.h"

ENetPacket* create_enet_packet( Buffer::Ptr buffer );
