#pragma once

#include "Tree.h"
#include "../Core.h"

namespace ooe
{
	//Struct holding map data
	class Map {
		friend class RRT;
	public:
		Map(){}
		Map(std::string d, int w, int h, char free, char obs) 
			: data(d), width(w), height(h), x_free(free), x_obs(obs) {}

	private:
		char x_free;
		char x_obs;
		size_t width;
		size_t height;
		std::string data;
	};


	//Class implementing the RRT algorithm
	class RRT
	{
	public:
		RRT();
		~RRT(void);

		//Build RRT
		std::shared_ptr<Tree> generateRRT(vec2 x_init, unsigned int K, unsigned int dt);

		void init(Map map);

		//Render Map to screen
		void renderMap(int obsid) const;

		//Render Tree vertices to screen
		void drawTree(int texture_id);

		//ratio of Map_size to Screen_size
		vec2 scale();

	private:
		//Compute new value
		vec2 newState(vec2 x_near, vec2 input, int delta_time);

		//Validate that x_new lies within x_free
		bool validate(vec2 x_new) const;

		std::shared_ptr<Tree> t_;
		Map map_;
		vec2 scale_;
		std::minstd_rand rand_;

		static bool initialized_;
	};
}
