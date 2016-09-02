#pragma once

#include "../scene/actor.h"

/**
 * @brief The Card class represents a card to be used by the summoners
 * Some can be:
 *		* Spawn creature
 *		* Increase creature stat temporarily
 *		* Poison on creature
 *		* Heal creature
 */

class Card
{
public:
	virtual ~Card();

	virtual void apply( Actor::SharedPtr actor ) = 0 ;
};
