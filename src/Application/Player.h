//UserControl iSystem
//Required Components: Position + sensitivity + Control
//Allows Dpad, Keypad, or both to be used for movement depending on which is passed as a parameter into componentManager().componentManager().getComponent

#pragma once

#include "Headers.h"

using namespace ooe;

//User iComponent holds information for user input
struct User : public iComponent
{
	float sensitivity;
	Rectangle boundary;
	const HAPI_TKeyboardData* keyboard;
	const HAPI_TControllerData* gamepad;
	const HAPI_TMouseData* mouse;

	vec2 velocity() { return velocity_; }

	User() : keyboard(nullptr), gamepad(nullptr), mouse(nullptr) {}

private:
	friend class Player;
	vec2 velocity_;
}; 

class Player : public iSystem
{
	virtual void update(std::shared_ptr<Entity> entity);

	void BoundtoBorder(vec2 pos, std::shared_ptr<User> input);
	vec2 GamePadControl(vec2 pos, std::shared_ptr<User> input);
	vec2 KeyboardControl(vec2 pos, std::shared_ptr<User> input);
};
