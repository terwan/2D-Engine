#pragma once

#include "../Core.h"

namespace ooe
{
	class Time
	{
	public:
		//return the internal engine time
		static uint32 time();

		//return the engine delta time
		static uint32 deltaTime();

		//the appropriate zero value for time
		static uint32 zero();

	private:
		static uint32 time_;

		Time(){}
	};
}