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
#include "../command/spawncommands.h"
#include "../command/aicommands.h"
#include "../command/commandprocessor.h"
#include "../textinputprocessor.h"

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
	void editorStep();
	void commandStep();
	void tryEnqueueCommand( Command::SharedPtr cmd );

	LD36* m_game;

	bool m_enableMouseTravel = true;
	Scene::SharedPtr m_scene;
	TextInputProcessor m_textInput;

	Spawner::SharedPtr m_spawner;
	SingleCommandProcessor m_commandProcessor;
	std::vector<Command::SharedPtr> m_spawnerCommands;
	int m_selectedSpawner;
	Command::SharedPtr m_deleteCommand;
	Command::SharedPtr m_pathfindCommand;


};


