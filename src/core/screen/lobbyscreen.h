#pragma once

#include <allegro5/allegro5.h>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/input/input.h>
#include <alligator/util/matrix.h>

#include "../textinputprocessor.h"

class LD36;

class LobbyScreen : public IScreen {
public:
	LobbyScreen(LD36* g);
	virtual ~LobbyScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override ;
	void hide() override ;

private:
	LD36* m_game;
	TextInputProcessor m_textInput;
	std::string m_failCxText;

};


