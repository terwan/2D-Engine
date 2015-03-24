//Entity Class
//Each Entity holds 0 or more Components which act as a storage unit for the entity's data

#pragma once

#include "Component.h"
#include "CManager.h"
#include "../Core.h"
#include "../Math/Vector2D.h"

namespace ooe
{
	struct Transform : public iComponent
	{
		vec2 translation;
		vec2 rotation;
		vec2 scale;
	};

	class Entity
	{
	public:
		Entity(std::string id);

		void setTag(std::string name);
		std::string tag() const;

		ComponentManager<iComponent>& componentManager() {return  component_manager_; }
		
	private:
		std::string tag_;
		ComponentManager<iComponent> component_manager_;
	}; 
}
