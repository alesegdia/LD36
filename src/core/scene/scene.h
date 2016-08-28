#pragma once

#include <vector>
#include <memory>
#include <alligator/util/matrix.h>
#include <alligator/camera/camera.h>

#include "entity.h"
#include "renderer.h"
#include "tilemap.h"

#include "../gameconfig.h"
#include "../assets.h"

class Scene
{
public:
	typedef std::shared_ptr<Scene> SharedPtr;
	typedef std::vector<Entity::SharedPtr> EntityList;
	typedef Matrix2D<Entity::SharedPtr> EntityMatrix;

	~Scene();

	Scene( Tilemap::SharedPtr map, Camera::SharedPtr map_camera );

	Entity::SharedPtr addPlayerEntity( Entity::SharedPtr entity );
	Entity::SharedPtr addEnemyEntity( Entity::SharedPtr entity );
	Entity::SharedPtr addWallEntity( Entity::SharedPtr entity );

	void setGroundTile( Vec2i tile, int value );
	void setTileAtIsoCoord( Vec2i iso_coord, int value );

	void render();
	Vec2i getTileAtIso( const Vec2i& iso_coord );

	bool isWalkableTile(const Vec2i &tile );

private:

	static bool CompareEntityRenderOrder( Entity::SharedPtr e1, Entity::SharedPtr e2 );

	EntityList m_playerEntities;
	EntityList m_enemyEntities;
	EntityList m_wallEntities;

	// for rendering
	EntityList m_allEntities;

	Tilemap::SharedPtr m_map;
	EntityMatrix::SharedPtr m_entityMatrix;
	IsometricTileMapRenderer::SharedPtr m_mapRenderer;
	Camera::SharedPtr m_mapCamera;

};
