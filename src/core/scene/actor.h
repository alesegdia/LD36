#pragma once

#include <memory>

#include "entity.h"

struct Stats
{
	float maxhp;
	float str;
	float def;
	float accuracy;
	float agility;
};

class Actor : public Entity
{
public:
	typedef std::shared_ptr<Actor> SharedPtr;

	Actor( ALLEGRO_BITMAP* sprite, Vec2f position = Vec2f(0,0) )
		: Entity( sprite, position )
	{

	}

	const Stats& stats() const
	{
		return m_stats;
	}

private:
	Stats m_stats;
	float m_health;
	float m_maxAP;

};
