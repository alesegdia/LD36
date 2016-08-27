#pragma once

#include <vector>
#include <memory>
#include <alligator/util/matrix.h>

#include "entity.h"

class Scene
{
public:
	typedef std::shared_ptr<Scene> SharedPtr;

	Scene( Matrix2Di::SharedPtr map )
		: m_map(map)
	{

	}

	void addPlayerEntity( Entity::SharedPtr entity )
	{
		m_playerEntities.push_back(entity);
	}

	void addEnemyEntity( Entity::SharedPtr entity )
	{
		m_enemyEntities.push_back(entity);
	}

	void setTile( Vec2i tile, int value )
	{
		if( tile.x() >= 0 && tile.x() < m_map->cols() &&
			tile.y() >= 0 && tile.y() < m_map->rows() )
		{
			m_map->set( tile.x(), tile.y(), 3 );
		}
	}

private:
	std::vector<Entity::SharedPtr> m_playerEntities;
	std::vector<Entity::SharedPtr> m_enemyEntities;
	Matrix2Di::SharedPtr m_map;

};
