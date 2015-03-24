#include "Application.h"
#include "../Application/World1.h"

void HAPI_Main()
{
	int screen_width = 700;
	int screen_height = 700;

	ooe::app.run(screen_width, screen_height, std::shared_ptr<ooe::iWorld>(new World1));
}