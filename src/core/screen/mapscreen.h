#pragma once

#include <allegro5/allegro5.h>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/input/input.h>
#include <alligator/util/matrix.h>

#include "../scene/scene.h"
#include "../scene/renderer.h"

class LD36;

class MapScreen : public IScreen {
public:
	MapScreen(LD36* g);
	virtual ~MapScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override ;
	void hide() override ;

private:

	LD36* m_game;
	IsometricTileMapRenderer::SharedPtr m_mapRenderer;
	Scene::SharedPtr m_gameMap;
	bool m_enableMouseTravel = false;

};


