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

	Entity::SharedPtr spawn( Entity::SharedPtr model, const Vec2i& tile_pos )
	{
		auto entity = Entity::Clone( model, Vec2f( tile_pos.x() * 16, tile_pos.y() * 16 ) );
		return m_scene->addPlayerEntity(entity);
	}

	void spawnSlime( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(0, 0), tile_pos);
	}

	void spawnSnake( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(1, 0), tile_pos);
	}

	void spawnGod( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(2, 0), tile_pos);
	}

	void spawnDemon( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(0, 1), tile_pos);
	}

	void spawnMagetoball( Vec2i tile_pos )
	{
		Entity::SharedPtr entity = makeEntityAtTile(Assets::instance->charactersSheet->getFrame(1, 1), tile_pos);
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
