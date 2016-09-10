#include "scene.h"

Scene::~Scene()
{
	m_allEntities.clear();
	m_playerEntities.clear();
	m_enemyEntities.clear();
}

Scene::Scene(Tilemap::SharedPtr map, Camera::SharedPtr map_camera)
	: m_floorMap(map),
	  m_mapCamera(map_camera)
{
	m_entityMatrix.reset(new EntityMatrix(m_floorMap->cols(), m_floorMap->rows(), nullptr));
	m_floorMapRenderer.reset(new MapRenderer(map, Assets::instance->mapTiles, GameConfig::ISO_TILE_SIZE));

}

Entity::SharedPtr Scene::addEntity(Entity::SharedPtr entity, EntityType entity_type)
{
	switch( entity_type )
	{
	case EntityType::Player: m_playerEntities.push_back(entity); break;
	case EntityType::Enemy: m_enemyEntities.push_back(entity); break;
	case EntityType::Wall: m_wallEntities.push_back(entity); break;
	}
	m_allEntities.push_back(entity);
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), entity );
	return entity;
}

void Scene::setGroundTile(Vec2i tile, int value)
{
	if( tile.x() >= 0 && tile.x() < m_floorMap->cols() &&
			tile.y() >= 0 && tile.y() < m_floorMap->rows() )
	{
		m_floorMap->set( tile.x(), tile.y(), value );
	}
}

void Scene::setTileAtIsoCoord(Vec2i iso_coord, int value)
{
	Vec2i pos = get_tile_at_iso(iso_coord + Vec2i(-m_mapCamera->x(), -m_mapCamera->y()));
	this->setGroundTile( pos, value );
}

void Scene::render()
{
	m_mapCamera->bind();
	m_floorMapRenderer->render();

	std::stable_sort(m_allEntities.begin(), m_allEntities.end(), &CompareEntityRenderOrder);

	for( auto e : m_allEntities )
	{
		e->render();
	}
}

Vec2i Scene::getTileAtIso(const Vec2i& iso_coord)
{
	return get_tile_at_iso(iso_coord + Vec2i(-m_mapCamera->x(), -m_mapCamera->y()));
}

bool Scene::isWalkableTile(const Vec2i& tile)
{
	return	fitsTilemap(tile) && m_entityMatrix->get(tile.x(), tile.y()) == nullptr;
}

void Scene::removeEntityAtOrthoTile(const Vec2i &ortho)
{
	if( fitsTilemap(ortho) )
	{
		Entity::SharedPtr to_remove = m_entityMatrix->get(ortho.x(), ortho.y());
		if( to_remove != nullptr )
		{
			removePlayerEntity( to_remove );
		}
	}
}

void Scene::removePlayerEntity(Entity::SharedPtr to_remove)
{
	m_entityMatrix->set(to_remove->tile().x(), to_remove->tile().y(), nullptr);
	removeEntityFromList(to_remove, m_playerEntities);
	removeEntityFromList(to_remove, m_allEntities);
}

void Scene::removeEntityFromList(Entity::SharedPtr entity, Scene::EntityList &list)
{
	list.erase(std::remove(list.begin(), list.end(), entity));
}

void Scene::drawPath(const std::vector<Vec2i> &nodes)
{
	for( auto n : nodes )
	{
		m_floorMap->set(n.x(), n.y(), 3);
	}
}

Entity::SharedPtr Scene::getEntityAt(const Vec2i &tile)
{
	if( fitsTilemap( tile ) )
	{
		return m_entityMatrix->get( tile.x(), tile.y() );
	}
	return nullptr;
}

void Scene::repositionUnit(Entity::SharedPtr entity, const Vec2f &new_pos)
{
	entity->setPosition(new_pos);
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), nullptr );
	entity->computeTile();
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), entity );
}

bool Scene::fitsTilemap(const Vec2i &tile)
{
	return	tile.x() >= 0 && tile.x() < m_entityMatrix->cols() &&
			tile.y() >= 0 && tile.y() < m_entityMatrix->rows();
}

bool Scene::CompareEntityRenderOrder(Entity::SharedPtr e1, Entity::SharedPtr e2)
{
	return e1->renderOrder() < e2->renderOrder();
}
