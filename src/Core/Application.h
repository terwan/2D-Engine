#pragma once

#include "World.h"
#include "Input\Input.h"
#include "PathGeneration\RRT.h"

namespace ooe
{
	class Application
	{
	public:
		Application(){}
		~Application(void);

		void run(int screen_width, int screen_height, std::shared_ptr<iWorld> default_world = std::shared_ptr<iWorld>());

		void addWorld(std::shared_ptr<iWorld> world);

		void destroy(void* object);

		void loadWorld(size_t id);
		void loadWorld(std::string tag);
		void loadFirstWorld();


		Input& input() { return input_; }
		RRT& rrt() { return rrt_; }

		static Application& getInstance();

	private:
		bool is_init_;
		RRT rrt_;
		Input input_;
		std::shared_ptr<iWorld> current_world_;
		std::vector<std::shared_ptr<iWorld>> world_array_;
		std::unordered_map<std::string, std::shared_ptr<iWorld>> world_map_;


		static bool instance_flag_;
		static Application* instance_;

		Application(const Application& other){}
		const Application& operator=(Application& other){}

		void update();
	};

#define app Application::getInstance()

}

