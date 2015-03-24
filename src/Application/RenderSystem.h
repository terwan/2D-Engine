//RenderSystem iSystem
//Draws Entities to a Screen

#pragma once

#include "Headers.h"

using namespace ooe;

struct Animation : public iComponent
{
	uint16	frame;
	Rectangle frame_dimension;

	Animation() : frame(1) {}
};

struct Model : public iComponent
{
	bool quick_draw;
	int sprite_id;

	Model() : sprite_id(-1), quick_draw(false) {}
};

struct Background : public Model
{
	//TODO: Implement this for scrolling backgrounds
};

class RenderSystem : public iSystem
{
private:
	void resetAnimation(std::shared_ptr<Entity> e);
	virtual void update(std::shared_ptr<Entity> entity);
};

