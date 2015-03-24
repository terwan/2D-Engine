//
// - Base class for Different Systems
// - Systems act as locks
// - During an update, an Entity must have the required key(getComponents), to activate the lock(update)
//		system then creates local variables of their required type, through what's returned by the entity
//		Each system then goes through another check to make sure, it's new local variables aren't null
//		if these variables aren't null, the system manipulates the data accordingly

#pragma once

#include "Entity.h"

namespace ooe
{
	//DO NOT call delete on getComponents in system.
	//Entities handle componentManager().componentManager().getComponent clean-up
	class iSystem
	{
		friend class Engine;
	protected:
		virtual ~iSystem(void) {}

		virtual void update(std::shared_ptr<Entity> entity) = 0;
	};
}