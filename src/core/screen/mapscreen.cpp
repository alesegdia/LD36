
#include "mapscreen.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <alligator/util/rng.h>
#include <alligator/input/input.h>

#include <iostream>
#include <memory>

#include "../ld36game.h"
#include "../assets.h"
#include "../gameconfig.h"


MapScreen::MapScreen( LD36* g )
	: m_game(g)
{
	Matrix2Di::SharedPtr map( new Matrix2Di(10, 10, {
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
	m_gameMap.reset(new Scene(map, m_game->m_camera2));
	m_spawner.reset(new Spawner(m_gameMap));

	m_spawnerCommands.push_back(std::make_shared<SlimeSpawnerCommand>(m_spawner));
	m_spawnerCommands.push_back(std::make_shared<SnakeSpawnerCommand>(m_spawner));
	m_spawnerCommands.push_back(std::make_shared<GodSpawnerCommand>(m_spawner));
	m_spawnerCommands.push_back(std::make_shared<DemonSpawnerCommand>(m_spawner));
	m_spawnerCommands.push_back(std::make_shared<MagnetoballSpawnerCommand>(m_spawner));

	m_deleteCommand = std::make_shared<RemoveEntity>( m_gameMap );
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

	m_game->m_camera2->move( dx, dy );

	if( m_game->editor() )
	{
		editorStep();
	}
}

void MapScreen::render()
{
	al_clear_to_color(al_map_rgb(255,255,255));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	m_gameMap->render();

	m_game->m_camera1->bind();
	char buffer[10];
	sprintf(buffer, "tool %d", m_selectedSpawner);
	al_draw_text(m_game->m_font, al_map_rgb(32, 128, 32), 0, 0, 0, buffer );
}

void MapScreen::hide()
{

}

void MapScreen::editorStep()
{

	if( Input::IsKeyJustPressed(ALLEGRO_KEY_Q) )
	{
		m_selectedSpawner = (m_selectedSpawner + 1) % m_spawnerCommands.size();
	}

	if( Input::IsKeyJustPressed(ALLEGRO_KEY_E))
	{
		m_selectedSpawner = std::max(0, m_selectedSpawner - 1);
	}

	if( Input::IsMouseButtonPressed(1) )
	{
		Vec2i tile = m_gameMap->getTileAtIso(Input::GetMousePosition());
		if( m_gameMap->isWalkableTile(tile) )
		{
			m_spawnerCommands[m_selectedSpawner]->reset();
			tryEnqueueCommand(m_spawnerCommands[m_selectedSpawner]);
			//(*m_spawnerCommands[m_selectedSpawner])(tile);
		}

	}

	if( Input::IsMouseButtonPressed(2) )
	{
		m_deleteCommand->reset();
		tryEnqueueCommand(m_deleteCommand);
	}

	commandStep();
}

void MapScreen::commandStep()
{
	if( m_runningCommand != nullptr )
	{
		if( m_runningCommand->status() != Command::Status::Ready )
		{
			Vec2i tile = m_gameMap->getTileAtIso(Input::GetMousePosition());
			(*m_runningCommand)(tile);
		}

		if( m_runningCommand->status() == Command::Status::Ready )
		{
			m_runningCommand = nullptr;
		}
	}
}

void MapScreen::tryEnqueueCommand(Command::SharedPtr cmd)
{
	if( m_runningCommand == nullptr || m_runningCommand->status() == Command::Status::Ready )
	{
		m_runningCommand = cmd;
	}
}


