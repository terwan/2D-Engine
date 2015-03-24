#include "AI.h"

/*
*Entities follow a path by attempting to align their position (top-left corner of sprite) with a node
*on the path between a start and end vec2. AI movement is still a bit buggy though... 
*At certain points, because there are too many nearby nodes, the ai gets stuck. Everything else, however, seems to work perfectly.
*/
void AI::update(std::shared_ptr<Entity> entity)
{
	if (!entity->componentManager().hasComponent<Logic>()) return;

	auto logic = entity->componentManager().getComponent<Logic>();
	auto transform = entity->componentManager().getComponent<Transform>();

	if (!logic->is_enabled_) return;

	std::shared_ptr<Tree> tree(new Tree);

	computeRoute(transform->translation, tree, logic);
	const vec2& destination = targetDestination(transform->translation, tree);

	//lerp ai from position to destination at a speed logic->speed
	const float max_step = engine.updateFrequency() - logic->speed;
	const float step_size = Time::deltaTime() - logic->speed;
	const float s = linearStep(0, max_step, step_size);
	transform->translation = lerp(transform->translation, destination, s);
}

void AI::computeRoute(vec2& entity_position, std::shared_ptr<Tree> tree, std::shared_ptr<Logic> logic)
{
	if (logic->target == vec2()) return; 

	auto end_node =  logic->tree.nearestNeighbour(logic->target);

	//Only compute a route if the current route is insufficient.
	auto current_end_node = tree->nearestNeighbour(logic->target);
	if (!tree->Nodes().empty() && current_end_node->vertex == end_node->vertex) return;

	auto start_node = logic->tree.nearestNeighbour(entity_position);

	Tree* start_route = new Tree;
	Tree* end_route = new Tree;

	//Split tree into two new trees which go from their respective
	//start nodes to their root. Both trees will contain the same root node.
	//This is done like this because there could be variable numbers of nodes between the respective ends, and the root.
	for (auto iter = start_node; iter != nullptr; iter = iter->parent) 
	{
		start_route->addNode(iter);
	} 
	for (auto iter = end_node; iter != nullptr; iter = iter->parent) 
	{
		end_route->addNode(iter);
	}

	/*Traverse each Tree list and find the first common node between both.
	*Since each node can only have one parent, when the 2 trees were created, they definitely contained the same root node
	*however, along the way, the could have both acquired a similar node in a lower level down in the tree.
	*We must the then find the lowest level in the original tree where these two nodes joined together as they went to the root.
	*This node is the hinge vec2 we will use to create our third, and final tree.
	*/
	bool found = false;
	auto start_nodes = start_route->Nodes();
	auto end_nodes = end_route->Nodes();
	std::shared_ptr<Node> join_point;

	for (auto start_iter = start_nodes.begin(); start_iter != start_nodes.end(); ++start_iter) 
	{
		for (auto end_iter = end_nodes.begin(); end_iter != end_nodes.end(); ++end_iter) 
		{
			if ((*start_iter)->vertex == (*end_iter)->vertex) {
				join_point = *start_iter;
				found = true;
			}
			if (found) break;
		}
		if (found) break;
	}

	/*
	*Rebuild our route by first deleting the old route, then building a new tree from start_nodes to end_nodes
	*with join_point being the hinge position where we link up these seperate trees
	*/

	for (auto n : start_nodes) 
	{
		tree->addNode(n);

		if (n->vertex == join_point->vertex) break;
	}
	for (auto n : end_nodes) 
	{
		if (n->vertex == join_point->vertex) break;

		tree->addNode(n);
	}

	//Clean up the memory created for the two temporary trees
	delete start_route;
	delete end_route;
}

vec2&& AI::targetDestination(vec2& entity_position, std::shared_ptr<Tree> tree)
{
	/*
	*If entity isn't on any tree path, it's first pointed to the start of the path
	*so that it can begin it's movement from the right place.
	*Once on path, entities can no longer traverse outside of their path.
	*/
	auto target_node = tree->nearestNeighbour(entity_position);

	//do something if entity is closer to the current node than current node is to it's neighbour
	if (entity_position.distance(target_node->vertex) <= target_node->edge.length()) {
		//Iterate over the list of nodes to find the entity_position of the current node in the node list
		auto nodes = tree->Nodes();
		for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) 
		{
			if (target_node->vertex == iter->get()->vertex) {
				//update current node to two nodes down, if next nodes aren't the end of the list(invalid node)		
				if (++iter == nodes.end()) return std::move(entity_position);

				auto next_iter = ++iter;
				if (next_iter == nodes.end()) return std::move(entity_position);

				target_node = *next_iter;
				return std::move(target_node->vertex);
			}
		}
	}
	return std::move(target_node->vertex);
}