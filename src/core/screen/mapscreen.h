#pragma once

#include <stack>
#include <queue>

#include <allegro5/allegro5.h>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/input/input.h>
#include <alligator/util/matrix.h>

#include "../scene/scene.h"
#include "../scene/renderer.h"
#include "../scene/spawner.h"
#include "../command/commands.h"

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

	void editorStep();
	void commandStep();

private:

	typedef std::function<void(Spawner*, const Vec2i&)> SpawnerTool;
	typedef std::vector<SpawnerTool> ToolSet;

	LD36* m_game;
	Scene::SharedPtr m_gameMap;
	bool m_enableMouseTravel = true;
	ToolSet m_callbackList;
	Spawner::SharedPtr m_spawner;
	std::queue<Command::SharedPtr> m_commandQueue;
	std::vector<Command::SharedPtr> m_spawnerCommands;
	int m_selectedSpawner;

};


