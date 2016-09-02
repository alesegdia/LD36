#pragma once

#include <cstdint>

/**
 * The protocol uses the first byte to determine the meaning of the packet.
 * Packets are structured like [ packetid | ... packet content ... ]
 * where packetid is an uint8_t from PacketType.
 *
 * The chat packet content is simply defined as:
 *		Chat packet:
 *			char char char ...
 *
 * For the rest of game commands, positions are given in tile position.
 * Elements enclosed in [square brackets] are optional.
 * Game command packets are defined as:
 *
 *		EntityAttack:	attacker_x attacker_y defender_x defender_y
 *			(attacker_x, attacker_y)	- position of the entity that attacks
 *			(defender_x, defender_y)	- position of the entity that blocks
 *
 *		UseCard:		card_id [affected_x affected_y] [player_id]
 *			(card_id)					- the ID of the card to use
 *			(affected_x affected_y)		- position of the affected entit
 *			(player_id)					- the ID of the affected player (only used if it's not the caster)
 *
 *		EntityMove:		entity_x entity_y entity_new_x entity_new_y
 *			(entity_x, entity_y)			- current entity's position
 *			(entity_new_x, entity_new_y)	- new entity's position
 *
 *		EntitySpawn:	entity_type spawn_x spawn_y
 *			(entity_type)		- type of the entity to be spawn (snake, goblin, etc)
 *			(spawn_x, spawn_y)	- position where the entity should be spawn
 *
 *		EndTurn: NO CONTENT
 *
 */

enum class PacketType : uint8_t
{
	Chat = 0,
	EntityAttack,
	UseCard,
	EntityMove,
	EntitySpawn,
	EndTurn
};

class Protocol
{
public:

};
