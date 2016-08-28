#include "aicommands.h"

std::vector<Vec2i> find_path(Scene::SharedPtr scene, Vec2i start_tile, Vec2i end_tile)
{
	TilemapModel model(scene);
	TilemapAStar astar(&model);
	TilemapModel::Node::Ptr start_node = std::make_shared<TilemapModel::Node>(start_tile.x(), start_tile.y());
	TilemapModel::Node::Ptr target_node = std::make_shared<TilemapModel::Node>(end_tile.x(), end_tile.y());
	start_node->G(0);
	start_node->H(model.hCost(start_node, target_node));
	start_node->computeF();
	astar.restartSearch(start_node, target_node);
	while( AStarSearchStatus::Running == astar.step() );
	astar.computeSolution();
	std::vector<Vec2i> nodes;
	for( auto n : astar.solution() )
	{
		nodes.push_back(Vec2i( n->x(), n->y() ));
	}
	return nodes;
}
