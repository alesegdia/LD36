#pragma once

#include <memory>
#include <allegro5/allegro.h>
#include <alligator/util/math.h>

#include "isometrictranslator.h"

class Entity
{
public:

	typedef std::shared_ptr<Entity> SharedPtr;

	Entity( ALLEGRO_BITMAP* sprite, Vec2f position = Vec2f(0, 0) )
		: m_sprite(sprite),
		  m_position(position)
	{

	}

	void render()
	{
		al_draw_bitmap(m_sprite, m_position.x(), m_position.y(), 0);
	}

	int renderOrder()
	{
		return int(m_position.x() + m_position.y());
	}

	void computeTile()
	{
		m_tile = get_tile_at_iso(Vec2i(int(m_position.x()), int(m_position.y())));
	}

private:
	ALLEGRO_BITMAP* m_sprite;
	Vec2f m_position;
	Vec2i m_tile;

};
