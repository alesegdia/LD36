#include "scene.h"

Scene::Scene(Tilemap::SharedPtr map, Camera::SharedPtr map_camera)
	: m_map(map),
	  m_mapCamera(map_camera)
{
	m_entityMatrix.reset(new EntityMatrix(m_map->cols(), m_map->rows(), nullptr));
	m_mapRenderer.reset(new IsometricTileMapRenderer(map, Assets::instance->mapTiles, GameConfig::ISO_TILE_SIZE));

}

Entity::SharedPtr Scene::addPlayerEntity(Entity::SharedPtr entity)
{
	m_playerEntities.push_back(entity);
	m_allEntities.push_back(entity);
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), entity );
	return entity;
}

Entity::SharedPtr Scene::addEnemyEntity(Entity::SharedPtr entity)
{
	m_enemyEntities.push_back(entity);
	m_allEntities.push_back(entity);
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), entity );
	return entity;
}

Entity::SharedPtr Scene::addWallEntity(Entity::SharedPtr entity)
{
	m_wallEntities.push_back(entity);
	m_allEntities.push_back(entity);
	m_entityMatrix->set( entity->tile().x(), entity->tile().y(), entity );
	return entity;
}

void Scene::setGroundTile(Vec2i tile, int value)
{
	if( tile.x() >= 0 && tile.x() < m_map->cols() &&
			tile.y() >= 0 && tile.y() < m_map->rows() )
	{
		m_map->set( tile.x(), tile.y(), value );
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
	m_mapRenderer->render();

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
	return	tile.x() >= 0 && tile.x() < m_entityMatrix->cols() &&
			tile.y() >= 0 && tile.y() < m_entityMatrix->rows() &&
			m_entityMatrix->get(tile.x(), tile.y()) == nullptr;
}

bool Scene::CompareEntityRenderOrder(Entity::SharedPtr e1, Entity::SharedPtr e2)
{
	return e1->renderOrder() < e2->renderOrder();
}
