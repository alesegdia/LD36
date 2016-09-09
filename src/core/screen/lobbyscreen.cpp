
#include "lobbyscreen.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <alligator/util/rng.h>
#include <alligator/input/input.h>

#include <iostream>
#include <memory>

#include "../ld36game.h"
#include "../assets.h"
#include "../gameconfig.h"


LobbyScreen::LobbyScreen( LD36* g )
	: m_game(g)
{
	Input::AddInputProcessor( &m_textInput );
}

LobbyScreen::~LobbyScreen()
{

}

void LobbyScreen::show()
{

}

void LobbyScreen::update(double delta)
{
	switch( m_game->state() )
	{
	case GameState::Disconnected:
		if( Input::IsKeyJustPressed( ALLEGRO_KEY_ENTER ) )
		{
			if( m_game->m_host->connect(m_textInput.str()) )
			{
				m_game->state( GameState::WaitingLobby );
				Input::RemoveInputProcessor(&m_textInput);
			}
			else
			{
				m_failCxText = "FAILED TO CONNECT TO ";
				m_failCxText += m_textInput.str();
			}
		}
		break;
	case GameState::WaitingLobby:
		break;
	case GameState::Ready:
		break;
	case GameState::MyTurn:
	case GameState::OtherTurn:
		break;
	}
}

void LobbyScreen::render()
{
	std::string str;
	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));
	m_game->m_camera1->bind();

	switch( m_game->state() )
	{
	case GameState::Disconnected:
		al_draw_text(m_game->m_font, al_map_rgb(128, 128, 128), 0, 0, 0, "DISCONNECTED");
		str = "IP: ";
		str +=  m_textInput.str();
		al_draw_text(m_game->m_font, al_map_rgb(128, 64, 64), 0, 20, 0, str.c_str());
		al_draw_text(m_game->m_font, al_map_rgb(128, 64, 64), 0, 40, 0, m_failCxText.c_str());
		break;
	case GameState::WaitingLobby:
		str = "CONNECTED TO ";
		str += m_textInput.str();
		al_draw_text(m_game->m_font, al_map_rgb(128, 32, 16), 0, 0, 0, str.c_str());
		break;
	case GameState::Ready:
		break;
	case GameState::MyTurn:
	case GameState::OtherTurn:
		break;
	}

}

void LobbyScreen::hide()
{

}

