#pragma once

#include "scene.h"
#include "entity.h"
#include "../assets.h"

class Spawner
{
public:
	typedef std::shared_ptr<Spawner> SharedPtr;

	Spawner( Scene::SharedPtr scene )
		: m_scene(scene)
	{

	}

	void spawnEnemy1( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(1, 0), tile_pos);
	}

private:

	Entity::SharedPtr makeEntityAtTile(ALLEGRO_BITMAP* sprite, const Vec2i& tile_pos )
	{
		Vec2f real_pos( tile_pos.x() * 16, tile_pos.y() * 16 );
		Entity::SharedPtr entity( new Entity(sprite, real_pos) );
		return m_scene->addPlayerEntity(entity);
	}

	Scene::SharedPtr m_scene;

};
