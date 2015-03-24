#include "Entity.h"
#include "../Engine.h"

namespace ooe
{
	Entity::Entity(std::string id) : tag_(id)
	{
		engine.addGameObject(std::shared_ptr<Entity>(this));
		component_manager_.addComponent<Transform>();
	}

	void Entity::setTag(std::string id)
	{
		tag_ = id;
	}

	std::string Entity::tag() const
	{
		return tag_;
	}

}


