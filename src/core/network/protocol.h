#pragma once

#include <cstdint>
#include <cstdlib>

class NetworkConfig
{
public:
	static constexpr int Port = 9838;
	static constexpr size_t NumClients = 32;
};

/**
Communication trace example:
	server				- awaiting connections
	clientA -> server	- connects
	server -> clientA	- ID1
	clientA				- annotates its ID as ID1
	clientB -> server	- connects
	server -> clientB	- ID2
	clientB				- annotates its ID as ID2
	clientA -> server	- ready
	clientB -> server	- ready
	server				- random starter... ID1
	server -> broadcast	- start game, starts ID1
	clientA -> server	- game packet
	server -> broadcast	- game packet
	clientA -> server	- game packet
	server -> broadcast	- game packet
	clientA -> server	- game packet
	server -> broadcast	- game packet
	clientA -> server	- ID1 endturn
	server -> broadcast	- ID1 endturn
	clientB -> server	- game packet
	server -> broadcast	- game packet
	clientB -> server	- game packet
	server -> broadcast	- game packet
	clientB -> server	- game packet
	server -> broadcast	- game packet
	clientB -> server	- ID2 endturn
	server -> broadcast	- ID2 endturn
 */

enum class GameState
{
	Disconnected,
		/** The player is disconnected */

	WaitingLobby,
		/** The player is connected. Possible action: press space to send a package to the server telling I'm ready. */

	Ready,
		/** When all players are ready, the server decides turns randomly and the game starts
			When the server sends a message telling the ID, if first is me, MyTurn, else, OtherTurn */

	MyTurn,
		/** When the state is MyTurn, the player will be able to perform actions.
			Delegates control of correct turn points and all the logic to the client, who sends packets */

	OtherTurn
		/** When the state is OtherTurn, the player will only be able to chat.
			The client will receive and interpret packets */

};

enum class ServerState
{
	AwaitingConnections,
		/** The server receives connections, computes a new unique peer ID and send it to it.
			The server receives Ready packets from clients and annotate it.
			When all players are ready, the server goes into Game mode.
			Connected peers can chat in this state */

	Game
		/** The server only broadcast received packets from now until the game is over */
};

/**
The protocol uses the first byte to determine the meaning of the packet.
Packets are structured as follows, where PTID is an uint8_t wrapped at PacketType enum.
		PTID | ... packet content ...

PTID is the Packet Type ID (uint8_t associated value).

Below there is a description of each PacketType.
Positions are given in tiles.
Elements enclosed in [square brackets] are optional.
 */

enum class PacketType : uint8_t
{
	AssignID = 0,
		/**   PTID | player_id			- ID assigned to the player */

	StartGame,
		/**   PTID | starter_id
			starter_id					- ID of the player who starts (chosen randomly by the server) */

	Ready,
		/**   PTID | player_id
			player_id					- ID of the player who was marked as ready */

	ChatMessage,
		/** Contains the message
		 *	  PTID | char char char ...  */

	EntityAttack,
		/**   PTID | attacker_x attacker_y defender_x defender_y
			attacker_x, attacker_y		- position of the entity that attacks
			defender_x, defender_y		- position of the entity that blocks */

	UseCard,
		/**   PTID | card_id [affected_x affected_y] [player_id]
			card_id						- the ID of the card to use
			affected_x affected_y		- position of the affected entit
			player_id					- the ID of the affected player (only used if it's not the caster) */

	EntityMove,
		/**   PTID | entity_x entity_y entity_new_x entity_new_y
			entity_x, entity_y			- current entity's position
			entity_new_x, entity_new_y	- new entity's position */

	EntitySpawn,
		/**   PTID | entity_type spawn_x spawn_y
			entity_type					- type of the entity to be spawn (snake, goblin, etc)
			spawn_x, spawn_y			- position where the entity should be spawn */

	EndTurn
		/**   PTID | player_id
			player_id					- ID of the player who just ended (sender, ideally) */

};



