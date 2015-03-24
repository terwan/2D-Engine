#include "PhysicSystem.h"

void PhysicSystem::update(std::shared_ptr<Entity> entity)
{
	if (entity->componentManager().getComponent<CollisionBox>() != nullptr)
	{
		auto cbox = entity->componentManager().getComponent<CollisionBox>();
		auto position = entity->componentManager().getComponent<Transform>()->translation;

		//Initialize collider on startup
		if (!cbox->initialized) {
			cbox->initialized = true;
			cbox->oldPos_ = position;
		}

		if (cbox->oldPos_ == position) return;

		cbox->collision_box.left = roundToInt(position.i);
		cbox->collision_box.top = roundToInt(position.j);

		//Check for collisions between entities
		CheckCollisions(entity);

		//update old position of collision box
		cbox->oldPos_ = position;
	}
}

void PhysicSystem::CheckCollisions(std::shared_ptr<Entity> entity)
{
	for (auto gameobj : engine.objects()) {
		//Avoid self checking
		if (entity == gameobj) continue;

		//Check for Box Collision
		if (gameobj->componentManager().getComponent<CollisionBox>() != nullptr) {
			if (!entity->componentManager().getComponent<CollisionBox>()->collision_box.completelyOutside(gameobj->componentManager().getComponent<CollisionBox>()->collision_box)) {

				entity->componentManager().getComponent<CollisionBox>()->collider_ = gameobj;
				gameobj->componentManager().getComponent<CollisionBox>()->collider_ = entity;

				//set position to previous value to stop further movement
				entity->componentManager().getComponent<Transform>()->translation = entity->componentManager().getComponent<CollisionBox>()->oldPos_;
			}
		}
	}
}