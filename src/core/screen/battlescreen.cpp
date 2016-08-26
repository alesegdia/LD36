#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/util/rng.h>
#include <alligator/input/input.h>

#include <iostream>

#include "../ld36game.h"

#include "battlescreen.h"
#include "../assets.h"


BattleScreen::BattleScreen( LD36* g )
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
								  0,1,1,1,0,0,1,1,1,0,
								  0,0,0,0,0,0,0,0,0,0,
							  }));


	m_mapRenderer.reset(new IsometricTileMapRenderer(m_map, Assets::instance->mapTiles, 32));
}

BattleScreen::~BattleScreen()
{

}

void BattleScreen::show()
{

}

void BattleScreen::update(double delta)
{

}

void BattleScreen::render()
{

	m_game->m_camera2.bind();

	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	m_mapRenderer->render();

}

void BattleScreen::hide()
{

}

