#include "Time.h"
#include "../Engine.h"

namespace ooe
{
	uint32 Time::time_ = zero();


	uint32 Time::deltaTime()
	{
		static uint32 old_time = zero();
		if (time() - old_time > engine.updateFrequency()) {
			old_time = time();
		}	
		return time() - old_time;
	}

	uint32 Time::time()
	{
		time_ = HAPI->GetTime();
		return time_;
	}

	uint32 Time::zero()
	{
		return 0;
	}
}