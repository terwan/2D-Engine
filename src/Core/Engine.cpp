#include "Engine.h"
#include "GFX\Graphics.h"
#include "Time\Time.h"
#include "../Application/RenderSystem.h" //Need to remove this hotfix

namespace ooe
{
	bool Engine::instance_flag_ = false;
	Engine* Engine::instance_;

	Engine& Engine::getInstance()
	{
		if(!instance_flag_) {
			instance_ = new Engine;
			instance_flag_ = true;
		}

		return *instance_;
	}

	//TODO: FIX Engine update time step
	void Engine::update()
	{
		for (auto entity : object_list_)
		{
			//Prune bad entities from list: TODO change this to happen during level load
			if (entity == nullptr) {
				object_list_.remove(entity);
				return;
			}

			if (renderer_ != nullptr) renderer_->update(entity);
			for (auto system : system_list_) 
				if (Time::deltaTime() == 0)
					system->update(entity);
		}
	}

	void Engine::setUpdateFrequency(uint32 value)
	{
		update_frequency_ = value;
	}

	uint32 Engine::updateFrequency()
	{
		return update_frequency_;
	}

	void Engine::addGameObject(std::shared_ptr<Entity> obj)
	{
		if (obj == nullptr) return;

		object_list_.push_back(obj);
		object_map_.insert(std::pair<std::string, std::shared_ptr<Entity>>(obj->tag(), obj));
	}


	std::list<std::shared_ptr<Entity>> Engine::objects()
	{
		return object_list_;
	}

	//Any entities with an empty-string-name will not be returned
	std::shared_ptr<Entity> Engine::object(std::string named_identifier)
	{
		try
		{
			if (!named_identifier.empty()) {
				auto obj = object_map_[named_identifier];
				return obj;
			}
		}
		catch (...) {
			return nullptr;
		}

		return nullptr;
	}
}