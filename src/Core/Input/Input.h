#pragma once

#include <HAPI_lib.h>

namespace ooe
{
	class Input
	{
	public:
		Input();
		~Input(){}

		void update();

		//Return handles for data input

		HAPI_TKeyboardData* KeyboardData();
		HAPI_TControllerData* GamepadData();
		HAPI_TMouseData* MouseData();

	private:
		HAPI_TKeyboardData keyboard_;
		HAPI_TControllerData gamepad_;
		HAPI_TMouseData mouse_;
	}; 
}