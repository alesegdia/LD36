#pragma once

#include <allegro5/allegro5.h>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/input/input.h>


class LD36;

class MenuScreen : public IScreen {
public:
	MenuScreen(LD36* g);
	virtual ~MenuScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override ;
	void hide() override ;

private:
	LD36* m_game;

	float timer = 0.f;
	float param = 1.f;
	int points = 0 ;

};


