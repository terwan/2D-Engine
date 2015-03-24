#pragma once

#include "../Core/World.h"
#include "Headers.h"

class World1 :
	public ooe::iWorld
{

protected:
	virtual void init();
	virtual void update();

private:
	std::minstd_rand min_rand_;
};

