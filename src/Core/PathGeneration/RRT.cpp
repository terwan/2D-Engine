#include "RRT.h"
#include "../GFX/Graphics.h"
#include "../Math/Utilities.hpp"

namespace ooe
{
	bool RRT::initialized_ = false;

	RRT::RRT()
	{
	}

	RRT::~RRT(void)
	{
		//delete t_;
	}

	void RRT::drawTree(int id)
	{
		if (!initialized_) return;

		for (auto t : t_->Nodes()) {
			gfx.quickdraw(t->vertex, id);
		}
	}

	/*Algorithm to generate random trees*/
	std::shared_ptr<Tree> RRT::generateRRT(vec2 x_init, unsigned int k, unsigned int dt) 
	{
		if (!initialized_) return nullptr;

		//scale initial values to that of screen
		x_init.i = (int)(x_init.i * scale_.i);
		x_init.j = (int)(x_init.j * scale_.j);

		//allocate memory for new tree
		t_ = std::shared_ptr<Tree>(new Tree);

		//c++11 random-number generation
		std::uniform_int_distribution<int> rand_x(0, map_.width * (int)scale_.i);
		std::uniform_int_distribution<int> rand_y(0, map_.height * (int)scale_.j);

		//Safety check to make sure x_init is valid, otherwise algorithm could potentialy break
		//If init is incorrect, for some reason, randomize init until it's valid
		while (!validate(x_init))
		{
			x_init = vec2(rand_x(rand_), rand_y(rand_));
		}
		t_->init(x_init);

		vec2 x_rand, x_near, x_new;
		vec2 u;

		for (uint16 i = 1; i < k; ++i) {
			x_rand = vec2(rand_x(rand_), rand_y(rand_));
			x_near = t_->nearestNeighbour(x_rand)->vertex;
			u = vec2(x_rand - x_near).unit();
			x_new = newState(x_near, u, dt);

			//Validate that x_new lies within x_free before adding it to the tree
			if (!validate(x_new))  
				--i;
			else 
			t_->newNode(x_near, x_new);
		}

		return t_;
	}

	void RRT::init(Map map)
	{
		if (initialized_) return;
		map_ = map;

		//If an invalid map size, flag RRT as uninitialized since nothing can be done anyway
		if (map_.width * map_.height <= 0) {
			initialized_ = false;
			return;
		}

		//Calculate map scaling factor rounded to nearest whole number
		uint16 x_scale = (uint16)round((double)gfx.width()/map_.width);
		uint16 y_scale = (uint16)round((double)gfx.height()/map_.height);
		scale_ = vec2((float)x_scale, (float)y_scale);

		initialized_ = true;
	}

	void RRT::renderMap(int obsid) const
	{
		//Because of the number of objects that need to be loaded at a time, this render method is purely visual 
		//and the obstacles aren't linked to the engine at all. Therefore, there will be no collidable objects. 
		//This is done because updating this with the engine slows down the entire program too much; eg. down to <10 fps.
		//The engine uses an O(n^2) loop which is something i need to optimize later before i render maps with the engine.

		if (!initialized_) return;

		for (uint16 j = 0; j < map_.height; ++j) {
			for (uint16 i = 0; i < map_.width; ++i) {
				if (map_.data[i + j * map_.width] == map_.x_obs) {
					int x = (int)round(i * scale_.i);
					int y = (int)round(j * scale_.j);
					gfx.quickdraw(vec2(x, y), obsid);
				}
			}
		}
	}

	vec2 RRT::scale()
	{
		return scale_;
	}


	vec2 RRT::newState(vec2 x_initial, vec2 input, int delta_time)
	{
		input.i = input.i * scale_.i;
		input.j = input.j * scale_.j;

		return x_initial + input * (float)delta_time;
	}

	bool RRT::validate(vec2 x_new) const
	{
		x_new.i = (int)(x_new.i / scale_.i);
		x_new.j = (int)(x_new.j / (scale_.j));

		uint16 offset = (uint16)x_new.i + (uint16)x_new.j * map_.width;

		if (map_.data[offset] != map_.x_free)
			return false;

		return true;
	}
}