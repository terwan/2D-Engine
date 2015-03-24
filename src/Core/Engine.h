//
//Engine Class
//Engine's responsible for updating every system

#pragma once

#include "CompSys\System.h"
#include "Core.h"

namespace ooe
{
	class Engine
	{
	public:

		void update();

		template <class _ISystem_T>
		std::shared_ptr<_ISystem_T> addSystem(); 

		void addGameObject(std::shared_ptr<Entity> obj);

		std::shared_ptr<Entity> object(std::string named_identifier);

		std::list<std::shared_ptr<Entity>> objects();

		void setUpdateFrequency(uint32 value);

		uint32 updateFrequency();

		static Engine& getInstance();
	private:
		uint32 update_frequency_;
		std::list<std::shared_ptr<Entity>> object_list_;
		std::unordered_map<std::string, std::shared_ptr<Entity>> object_map_;
		std::list<std::shared_ptr<iSystem>> system_list_;
		std::shared_ptr<iSystem> renderer_; //quick fix to differentiate renderer. need to fix

		static bool instance_flag_;
		static Engine* instance_;


		Engine() {}
		Engine(const Engine&) {}
		Engine& operator=(const Engine&){}
	};

#define engine Engine::getInstance()




	/**********************************************
	*Engine templated functions
	**********************************************/

	//Definition for add system template
	template <class _ISystem_T>
	std::shared_ptr<_ISystem_T> Engine::
		addSystem()
	{
		//Engine can only hold 1 of each system, 
		//so delete new system if it's a duplicate.
		for (auto s : system_list_) 
		{
			if (typeid(*s) == typeid(_ISystem_T)) {
				return nullptr;
			}
		}

		//allocate memory for the new system
		auto system = std::shared_ptr<_ISystem_T>(new _ISystem_T);

		//Determine whether system is renderer and attach to renderer if it is
		if (typeid(_ISystem_T) == typeid(RenderSystem)) {
			renderer_ = system;
		} 
		//Else add it to the list of systems
		else {
			system_list_.push_back(system);
		}

		return system;
	}
}