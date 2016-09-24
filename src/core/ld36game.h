#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <memory>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/camera/camera.h>

#include "network/client.h"
#include "network/protocol.h"

class MenuScreen;
class MapScreen;
class LobbyScreen;

class LD36 : public Game {

public:

	LD36 (int sw, int sh, bool editor = true , bool single = false);
	virtual ~LD36();

	int create(int argc, char **argv) override ;
	void dispose() override ;
	void update(double delta) override ;

	// all screens
	std::shared_ptr<MenuScreen> m_menuScreen;
	std::shared_ptr<LobbyScreen> m_lobbyScreen;
	std::shared_ptr<MapScreen> m_mapScreen;

	ALLEGRO_FONT* m_font = nullptr;
	ALLEGRO_FONT* m_fontBig = nullptr;

	Camera::SharedPtr m_camera1;
	Camera::SharedPtr m_camera2;
	Camera::SharedPtr m_camera3;

	Client::SharedPtr m_host;

	GameState state()
	{
		return m_gameState;
	}

	void state( GameState gs )
	{
		m_gameState = gs;
	}

	bool editor();
	void network()
	{
		//Buffer* buffer = m_host->pollEvent();
	}

private:
	bool m_editor;
	bool m_single;
	GameState m_gameState = GameState::Disconnected;

};

