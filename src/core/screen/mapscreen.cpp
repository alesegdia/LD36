
#include "mapscreen.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <alligator/util/rng.h>
#include <alligator/input/input.h>

#include <iostream>

#include "../ld36game.h"
#include "../assets.h"
#include "../gameconfig.h"


MapScreen::MapScreen( LD36* g )
	: m_game(g)
{
	m_map.reset(new Matrix2Di(10, 10, {
								  0,0,0,0,0,0,0,0,0,0,
								  0,1,1,1,0,0,1,1,1,0,
								  0,1,2,0,0,0,0,2,1,0,
								  0,1,0,0,0,0,0,0,1,0,
								  0,0,0,3,3,3,3,0,0,0,
								  0,0,0,0,3,3,0,0,0,0,
								  0,1,0,0,0,0,0,0,1,0,
								  0,1,2,0,0,0,0,2,1,0,
								  0,1,1,1,3,3,1,1,1,0,
								  0,0,0,0,0,0,0,0,0,0,
							  }));
	m_mapRenderer.reset(new IsometricTileMapRenderer(m_map, Assets::instance->mapTiles, GameConfig::ISO_TILE_SIZE));
	m_gameMap.reset(new Map(m_map));
}

MapScreen::~MapScreen()
{

}

void MapScreen::show()
{

}

void MapScreen::update(double delta)
{
	const float MoveSpeed = 8.f;
	float dx, dy;
	dx = dy = 0;
	const float portion = GameConfig::WINDOW_WIDTH / 16;

	if( Input::IsKeyDown(ALLEGRO_KEY_RIGHT) || (m_enableMouseTravel && Input::GetMousePosition().x() > GameConfig::WINDOW_WIDTH * GameConfig::CAMERA_SCALE - portion) )
	{
		dx = -MoveSpeed;
	}
	else if( Input::IsKeyDown(ALLEGRO_KEY_LEFT) || (m_enableMouseTravel && Input::GetMousePosition().x() < portion) )
	{
		dx = MoveSpeed;
	}

	if( Input::IsKeyDown(ALLEGRO_KEY_UP) || (m_enableMouseTravel && Input::GetMousePosition().y() < portion) )
	{
		dy = MoveSpeed / 2;
	}
	else if( Input::IsKeyDown(ALLEGRO_KEY_DOWN) || (m_enableMouseTravel && Input::GetMousePosition().y() > GameConfig::WINDOW_HEIGHT * GameConfig::CAMERA_SCALE - portion) )
	{
		dy = -MoveSpeed / 2;
	}

	m_game->m_camera2.move( dx, dy );

	if( Input::IsMouseButtonPressed(1) )
	{
		Vec2i pos = m_mapRenderer->getTileAtIso(Input::GetMousePosition() + Vec2i(-m_game->m_camera2.x(), -m_game->m_camera2.y()));
		m_gameMap->setTile( pos, 3 );
	}

}

void MapScreen::render()
{

	m_game->m_camera2.bind();

	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	m_mapRenderer->render();

}

void MapScreen::hide()
{

}


