#pragma once

#include "Vector2D.h"
#include "../Core.h"

/*---
- Header file containing declaration of several functions 
- Functions provide some form of indivual and/or combined matrix transformations
- Functions are All listed in DESCENDING alphabetical order within the header file AND implementation file
*/

namespace ooe
{
	float smoothStep(float start, float stop, float value);

	//return the + or - sign of value
	char sign(float value);

	//Set the colour of a pixel on screen
	void setPixelColour(uchar* pixel_location, HAPI_TColour);

	//round off a decimal to it's nearest whole number
	double round(double value);
	int roundToInt(double value);

	//Calculate the memory offset of a pixel on screen
	uint32 pixelOffset(vec2 position, uint16 width);

	//Parse a string to a float
	float parse(std::string str);

	float linearStep(float start, float stop, float value);

	vec2 lerp(vec2 p0, vec2 p1, float s);

	float clamp(float min, float max, float current_value);
}
