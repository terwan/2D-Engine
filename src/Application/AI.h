#pragma once

#include "Headers.h"

using namespace ooe;

struct Logic : public iComponent
{
	float speed;
	vec2 target;
	Tree tree;

	Logic() : speed(0.f) {}
};

class AI : public iSystem
{

private:
	virtual void update(std::shared_ptr<Entity> entity);

	//Compute route_ by determining a single path from entity_position to logic->target, from all the available paths in Logic::Tree
	void computeRoute(vec2& entity_position, std::shared_ptr<Tree> tree, std::shared_ptr<Logic> logic);

	//Determine which node, in the route, should be the target for the entity and return it's position
	vec2&& targetDestination(vec2& entity_position, std::shared_ptr<Tree> tree);
};