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

	Entity::SharedPtr addEntity( Entity::SharedPtr entity, EntityType entity_type );
	void setGroundTile( Vec2i tile, int value );
	void setTileAtIsoCoord( Vec2i iso_coord, int value );

	void render();
	Vec2i getTileAtIso( const Vec2i& iso_coord );
	bool isWalkableTile(const Vec2i &tile );

	void removeEntityAtOrthoTile( const Vec2i& ortho );

	void removePlayerEntity( Entity::SharedPtr to_remove );

	void removeEntityFromList( Entity::SharedPtr entity, EntityList& list );

	void drawPath( const std::vector<Vec2i>& nodes );

	Entity::SharedPtr getEntityAt( const Vec2i& tile );

	void repositionUnit( Entity::SharedPtr entity, const Vec2f& new_pos );

private:

	bool fitsTilemap( const Vec2i& tile );

	static bool CompareEntityRenderOrder( Entity::SharedPtr e1, Entity::SharedPtr e2 );

	EntityList m_playerEntities;
	EntityList m_enemyEntities;
	EntityList m_wallEntities;

	// for rendering
	EntityList m_allEntities;

	EntityMatrix::SharedPtr m_entityMatrix;

	Tilemap::SharedPtr m_floorMap;
	IsometricTileMapRenderer::SharedPtr m_floorMapRenderer;

	Tilemap::SharedPtr m_overlayMap;
	IsometricTileMapRenderer::SharedPtr m_overlayMapRenderer;

	Camera::SharedPtr m_mapCamera;

};
