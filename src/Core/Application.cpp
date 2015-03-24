#include "Application.h"
#include "World.h"
#include "Engine.h"
#include "GFX\Graphics.h"

//**************************************
#include "../Application/AI.h"
#include "../Application/PhysicSystem.h"
#include "../Application/Player.h"
#include "../Application/RenderSystem.h" 
//************************************ sort out these includes; maybe some of these systems should be core


namespace ooe
{
	bool Application::instance_flag_ = false;
	Application* Application::instance_;

	Application::~Application(void)
	{
		HAPI->SetControllerRumble(0, 0, 0);

		delete &engine;
		delete &gfx;
	}

	Application& Application::getInstance()
	{
		if(!instance_flag_) {
			instance_ = new Application;
			instance_flag_ = true;
		}

		return *instance_;
	}

	void Application::run(int screen_width, int screen_height, std::shared_ptr<iWorld> default_world)
	{
		if ((screen_width * screen_height) <= 0 || !gfx.init(screen_width, screen_height)) {
			HAPI->DebugText("\n#Error:\n\t->Failed to initialize window; Make sure width and height are valid number");
			return;
		}

		engine.setUpdateFrequency(30);

		//**************************
		engine.addSystem<AI>();
		engine.addSystem<Player>();
		engine.addSystem<PhysicSystem>();
		engine.addSystem<RenderSystem>();
		//*************************


		addWorld(default_world);
		loadFirstWorld();

		is_init_ = true;

		update();
	}

	void Application::addWorld(std::shared_ptr<iWorld> world)
	{
		if (world == nullptr) return;
		world_array_.push_back(world);
		world_map_.insert(std::pair<std::string, std::shared_ptr<iWorld>>(world->tag(), world));
	}

	void Application::destroy(void* object)
	{
		delete object;
		object = nullptr;
	}


	void Application::loadWorld(size_t id) 
	{
		if (id >= world_array_.size()) return;
		current_world_= world_array_[id];
		current_world_->init();
	}

	void Application::loadWorld(std::string tag)
	{
		try
		{
			if (!tag.empty()) {
				current_world_ = world_map_[tag];
				current_world_->init();
			}
		}
		catch (...) {
			return;
		}
	}

	void Application::loadFirstWorld()
	{
		if(world_array_.empty()) return;

		current_world_ = world_array_.front();
		current_world_->init();
	}


	void Application::update()
	{
		if (!is_init_) return;

		while(HAPI->Update()) {
			if(current_world_ != nullptr) current_world_->update();
			input_.update();
			engine.update();
		}

		delete &app;
	}

}