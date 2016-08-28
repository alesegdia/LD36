#pragma once

#include <alligator/input/input.h>

#include "astartilemapmodel.h"
#include "command.h"

std::vector<Vec2i> find_path( Scene::SharedPtr scene, Vec2i start_tile, Vec2i end_tile );

class PathfindCommand : public Command
{
public:
	PathfindCommand(Scene::SharedPtr scene)
		: Command("PathFind"),
		  m_scene(scene),
		  m_status(0)
	{

	}

	void delegate(const Vec2i &tile) override
	{
		if( m_status == 0 && Input::IsMouseButtonJustPressed(1) )
		{
			if( m_scene->isWalkableTile(tile) )
			{
				m_startTile = tile;
				m_status++;
			}
			status( Command::Status::Running );
		}
		else if( m_status == 1 && Input::IsMouseButtonJustPressed(1) )
		{
			if( m_scene->isWalkableTile(tile) )
			{
				m_endTile = tile;
				m_status++;
				m_scene->drawPath( find_path( m_scene, m_startTile, m_endTile ) );
				status( Command::Status::Ready );
			}
			else
			{
				status( Command::Status::Running );
			}
		}
		fflush(0);
	}

	void reset() override
	{
		m_status = 0;
		Command::reset();
	}

private:
	Scene::SharedPtr m_scene;
	uint8_t m_status;
	Vec2i m_startTile;
	Vec2i m_endTile;

};


class MoveEntityCommand : public Command
{
public:
	MoveEntityCommand( Scene::SharedPtr scene )
		: Command("MoveEntity"),
		  m_scene(scene)
	{

	}

	void delegate(const Vec2i &tile)
	{
		if( Input::IsMouseButtonJustPressed(1) )
		{
			switch( m_status )
			{
			case 0: // select unit to move
				m_selectedUnit = m_scene->getEntityAt( tile );
				if( m_selectedUnit != nullptr )
				{
					m_status++;
				}
				status( Command::Status::Running );
				break;
			case 1: // select place to move and perform search
				if( m_scene->isWalkableTile(tile) )
				{
					m_targetTile = tile;
					m_path = find_path( m_scene, m_selectedUnit->tile(), m_targetTile );
					m_status++;
				}
				status( Command::Status::Running );
				break;
			case 2: // move between nodes until reach
				if( m_currentNode < m_path.size() - 1 )
				{
					if( m_transitioning == 1.f )
					{
						m_transitioning = 0;
						m_fromTile = m_path[m_currentNode];
						m_toTile = m_path[m_currentNode + 1];
					}
					else
					{
						m_transitioning += 0.1f;
						auto pos = lerp(m_fromTile, m_toTile, m_transitioning);
						pos.set( pos.x() * 16, pos.y() * 16 );
						m_selectedUnit->setPosition(Vec2f(pos.x(), pos.y()));
					}
					status( Command::Status::Running );
				}
				else
				{
					status( Command::Status::Ready );
				}
				break;
			}
		}
	}

	void reset() override
	{
		m_status = 0;
		m_selectedUnit = nullptr;
		m_currentNode = 0;
		Command::reset();
	}

private:
	Scene::SharedPtr m_scene;
	uint8_t m_status;
	Entity::SharedPtr m_selectedUnit;
	Vec2i m_targetTile;
	std::vector<Vec2i> m_path;
	Vec2i m_fromTile;
	Vec2i m_toTile;

	size_t m_currentNode = 0;
	float m_transitioning = 0;
};
