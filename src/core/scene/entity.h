#pragma once

#include <memory>
#include <allegro5/allegro.h>
#include <alligator/util/math.h>

#include "isometrictranslator.h"

class Entity
{
public:

	typedef std::shared_ptr<Entity> SharedPtr;

	static Entity::SharedPtr Clone( Entity::SharedPtr model, Vec2f position )
	{
		Entity::SharedPtr clone(new Entity(model->m_sprite, position));
		// ... copy other params ...
		return clone;
	}

	Entity( ALLEGRO_BITMAP* sprite, Vec2f position = Vec2f(0, 0) )
		: m_sprite(sprite),
		  m_position(position)
	{
		std::cout << "Done at " << m_position.x() << ", " << m_position.y() << std::endl;
		computeTile();
	}

	void render()
	{
		Vec2i iso = ortho_to_iso(Vec2i(m_position.x() - 16, m_position.y() - 16));
		al_draw_bitmap(m_sprite, iso.x(), iso.y(), 0);
	}

	int renderOrder()
	{
		return int(m_position.x() + m_position.y());
	}

	void computeTile()
	{
		m_tile = Vec2i(int(m_position.x() / 16.f), int(m_position.y() / 16.f));
	}

	const Vec2i& tile()
	{
		return m_tile;
	}

	const Vec2f& position()
	{
		return m_position;
	}

	void setPosition( const Vec2f& pos )
	{
		m_position = pos;
	}

private:
	ALLEGRO_BITMAP* m_sprite;
	Vec2f m_position;
	Vec2i m_tile;

};
