#include "Player.h"

void Player::update(std::shared_ptr<Entity> entity)
{
	//Continue only if entity has User component
	if (entity->componentManager().getComponent<User>() != nullptr) {
		auto input = entity->componentManager().getComponent<User>();
		auto position = entity->componentManager().getComponent<Transform>()->translation;

		if (!input->is_enabled_) return;

		//Ensure entity can't pass it's assigned borders
		BoundtoBorder(position, input);

		const float max_step = engine.updateFrequency() + input->sensitivity;
		const float step_size = Time::deltaTime() + input->sensitivity;
		const float s = linearStep(0, max_step, step_size);
		vec2 destination;

		destination = (input->gamepad != nullptr) ? GamePadControl(position, input) : position;
		destination = (input->keyboard != nullptr) ? KeyboardControl(position, input) : position;

		//lerp between position and destination
		input->velocity_ = destination - position;
		position = lerp(position, destination, s);
	}
}


//DPAD Up, Down, Left, Right - Left Thumbstick
vec2 Player::GamePadControl(vec2 pos, std::shared_ptr<User> input)
{
	float sensitivity = input->sensitivity;
	//normalize the value returned by gamepad to -1 to 1
	const float normalizingFactor = powf(2, 15);
	const float normalizeY = input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] / normalizingFactor;
	const float normalizeX = input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] / normalizingFactor;

	//Scale up normalized values so that dpad sensitivity and stick sensitivity are same
	const float leftY = normalizeY * sensitivity;	
	const float leftX = normalizeX * sensitivity;

	//Manipulate position based on DPAD input
	if (input->gamepad->digitalButtons[HK_DIGITAL_DPAD_UP]) {
		return pos + vec2(0, -sensitivity);

	} else if (input->gamepad->digitalButtons[HK_DIGITAL_DPAD_DOWN]) {
		return pos + vec2(0, sensitivity);

	} else if (input->gamepad->digitalButtons[HK_DIGITAL_DPAD_LEFT]) {
		return pos + vec2(-sensitivity, 0);

	} else if (input->gamepad->digitalButtons[HK_DIGITAL_DPAD_RIGHT]) {
		return pos + vec2(sensitivity, 0);
	}

	//Ensure very low input values are discarded so that there isn't random input when joystick should be centered
	//If input isn't in deadzone, manipulate position based on joystick input
	if (input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < HK_GAMEPAD_LEFT_THUMB_DEADZONE &&
		input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > -HK_GAMEPAD_LEFT_THUMB_DEADZONE &&
		input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < HK_GAMEPAD_LEFT_THUMB_DEADZONE &&
		input->gamepad->analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > -HK_GAMEPAD_LEFT_THUMB_DEADZONE) {
			return pos;
	} else if(leftY || leftX) {
		return pos + vec2(leftX, -leftY);
	}

	return pos;
}

//Manipulates Position based on keypresses;
//WASD - QEZC - UP/Left/Right/Down
vec2 Player::KeyboardControl(vec2 pos, std::shared_ptr<User> input)
{
	bool UpLeft = input->keyboard->scanCode[HK_UP] & input->keyboard->scanCode[HK_LEFT];
	bool UpRight = input->keyboard->scanCode[HK_UP] & input->keyboard->scanCode[HK_RIGHT];
	bool DownLeft = input->keyboard->scanCode[HK_DOWN] & input->keyboard->scanCode[HK_LEFT];
	bool DownRight = input->keyboard->scanCode[HK_DOWN] & input->keyboard->scanCode[HK_RIGHT];
	float sensitivity = input->sensitivity;


	if (input->keyboard->scanCode[ HK_ESCAPE ]) {	
		HAPI->Close();

	} else if (input->keyboard->scanCode[ HK_F1 ]) {	
		HAPI->SetShowFPS(true);

	} else if (input->keyboard->scanCode[ HK_F2 ]) {
		HAPI->SetShowFPS(false);
	}

	if (UpLeft) {
		return pos + vec2(-sensitivity, -sensitivity);

	} else if (UpRight) {
		return pos + vec2(sensitivity, -sensitivity);

	} else if (DownLeft) {
		return pos + vec2(-sensitivity, sensitivity);

	} else if (DownRight) {
		return pos + vec2(sensitivity, sensitivity);

	} else if (input->keyboard->scanCode[HK_UP] || input->keyboard->scanCode['W']) {
		return pos + vec2(0, -sensitivity);

	} else if (input->keyboard->scanCode[HK_DOWN] || input->keyboard->scanCode['S']) {
		return pos + vec2(0, sensitivity);

	} else if (input->keyboard->scanCode[HK_LEFT] || input->keyboard->scanCode['A']) {
		return pos + vec2(-sensitivity, 0);

	} else if (input->keyboard->scanCode[HK_RIGHT] || input->keyboard->scanCode['D']) {
		return pos + vec2(sensitivity, 0);
	}

	return pos;
}

void Player::BoundtoBorder(vec2 pos, std::shared_ptr<User> input)
{
	//Clamp positions to a boundary they cannot pass
	if (input->boundary.width ==  0 && input->boundary.height ==0 ) return;

	pos = vec2(
		std::max((int)pos.i, input->boundary.left),
		std::max((int)pos.j, input->boundary.top));

	pos = vec2(
		std::min((int)pos.i, input->boundary.left + input->boundary.width),
		std::min((int)pos.j, input->boundary.top + input->boundary.height));
}