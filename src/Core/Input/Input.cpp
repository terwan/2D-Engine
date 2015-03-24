#include "Input.h"

namespace ooe
{
	Input::Input()
	{
		HAPI->SetShowFPS(true);
	}

	void Input::update()
	{
		KeyboardData();
		GamepadData();
		MouseData();
	}

	HAPI_TKeyboardData* Input::KeyboardData()
	{
		if (!HAPI->GetKeyboardData(&keyboard_)) return nullptr;
		return &keyboard_;
	}

	HAPI_TControllerData* Input::GamepadData()
	{
		if (!HAPI->GetControllerData(0, &gamepad_)) return nullptr;
		return &gamepad_;
	}

	HAPI_TMouseData* Input::MouseData()
	{
		if (!HAPI->GetMouseData(&mouse_)) return nullptr;
		return &mouse_;
	}
}