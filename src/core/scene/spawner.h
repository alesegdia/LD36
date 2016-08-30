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

	Entity::SharedPtr spawn( Entity::SharedPtr model, const Vec2i& tile_pos, EntityType entity_type )
	{
		auto entity = Entity::Clone( model, Vec2f( tile_pos.x() * 16, tile_pos.y() * 16 ) );
		return m_scene->addEntity(entity, entity_type);
	}

private:
	Scene::SharedPtr m_scene;

};
