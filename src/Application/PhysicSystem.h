//
//	-Header file for the PhysicSystem Class which contains the entire PhysicSystem iSystem
//	
//	-> Functions:
//		-> +CheckCollisions(list of entities)
//		-> +CollisionDetected()
//		-> +Nearing()

#pragma once

#include "Headers.h"

using namespace ooe;

struct iCollision : public iComponent
{
	friend class PhysicSystem;

	iCollision() : initialized(false) {}
protected:
	vec2 oldPos_;
	std::shared_ptr<Entity> collider_;
	bool initialized;
};

struct CollisionBox : public iCollision
{
	Rectangle collision_box;
};

struct CollisionSphere : public iCollision
{
	//Add shapes class with derived shapes - Rectangle, Circle, Cyclinder(?), triangle(?), etc...
};

class PhysicSystem : public iSystem
{
private:
	//update the collision box of every entity within the world
	virtual void update(std::shared_ptr<Entity> entity);

	//Determine whether a collision has occured
	void CheckCollisions(std::shared_ptr<Entity> entities);
};
