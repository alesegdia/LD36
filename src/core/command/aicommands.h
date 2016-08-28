#pragma once

#include <alligator/input/input.h>

#include "astartilemapmodel.h"
#include "command.h"

class PathfindCommand : public Command
{
public:
	PathfindCommand(Scene::SharedPtr scene)
		: m_astarModel(scene),
		  m_astar(&m_astarModel),
		  m_status(0)
	{

	}

	void delegate(const Vec2i &tile) override
	{
		if( m_status == 0 && Input::IsMouseButtonJustPressed(1) )
		{
			if( m_astarModel.scene()->isWalkableTile(tile) )
			{
				m_startTile = tile;
				m_status++;
				printf("Selected start tile\n");
			}
			status( Command::Status::Running );
		}
		else if( m_status == 1 && Input::IsMouseButtonJustPressed(1) )
		{
			if( m_astarModel.scene()->isWalkableTile(tile) )
			{
				m_endTile = tile;
				m_status++;
				printf("Selected end tile\n");
				TilemapModel::Node::Ptr start_node = std::make_shared<TilemapModel::Node>(m_startTile.x(), m_startTile.y());
				TilemapModel::Node::Ptr target_node = std::make_shared<TilemapModel::Node>(m_endTile.x(), m_endTile.y());
				start_node->G(0);
				start_node->H(m_astarModel.hCost(start_node, target_node));
				start_node->computeF();
				m_astar.restartSearch(start_node, target_node);
				while( AStarSearchStatus::Running == m_astar.step() );
				std::cout << m_astar.processedNodes() << std::endl;
				m_astar.computeSolution();
				m_astarModel.scene()->drawPath( transformNodesToVec2i(m_astar.solution()));
				status( Command::Status::Ready );
			}
		}
		fflush(0);
	}

	void reset() override
	{
		m_status = 0;
		Command::reset();
	}

	std::vector<Vec2i> transformNodesToVec2i( const std::vector<TilemapModel::NodePtr>& astarnodes )
	{
		std::vector<Vec2i> nodes;
		for( auto n : astarnodes )
		{
			nodes.push_back(Vec2i( n->x(), n->y() ));
		}
		return nodes;
	}

private:
	TilemapModel m_astarModel;
	TilemapAStar m_astar;

	uint8_t m_status;
	Vec2i m_startTile;
	Vec2i m_endTile;

};
