#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/util/rng.h>

#include <iostream>

#include "menuscreen.h"
#include "../ld36game.h"
#include "../assets.h"


MenuScreen::MenuScreen( LD36* g )
{
	m_game = g;
}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::show()
{

}

void MenuScreen::update(double delta)
{
	timer += delta * 10;
}

void MenuScreen::render()
{

	m_game->m_camera2->bind();

	al_clear_to_color(al_map_rgb(63,63,116));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	al_draw_text(m_game->m_fontBig, al_map_rgb(203, 219, 252), 15, 11, 0, "Pheee");
	al_draw_text(m_game->m_fontBig, al_map_rgb(203, 219, 252), 15, 31, 0, "Strew");
	al_draw_text(m_game->m_fontBig, al_map_rgb(203, 219, 252), 15, 51, 0, "Quest");

}

void MenuScreen::hide()
{

}

