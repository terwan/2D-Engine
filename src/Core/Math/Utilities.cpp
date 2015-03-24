#include "Utilities.hpp"

#include <sstream>

/*---
-A collection of utility functions
*/

namespace ooe
{
	float smoothStep(float start, float stop, float value)
	{
		value = linearStep(start, stop, value);

		auto valCube = pow(value,3);
		return valCube * (value * (6*value - 15) + 10);
	}

	char sign(float value)
	{
		char sign = (value < 0.f) ? -1 : +1;

		return sign;
	}

	void setPixelColour(uchar* pixelPosition, HAPI_TColour colour)
	{
		HAPI_TColour pixelColour(colour.red, colour.green, colour.blue, 255);
		memcpy(pixelPosition, &pixelColour, 4);
	}

	double round(double value)
	{
		double real;

		//If the absolute value of value is greater than 0.5
		//return number rounded up or down
		//depending on whether it's positive or negative
		if (abs(modf(value, &real)) >= 0.5) {
			return value >= 0 ? ceil(value) : floor(value);
		} else {
			return value < 0 ? ceil(value) : floor(value);
		}
	}

	int roundToInt(double value)
	{
		double real;
		double returnValue;

		//If the absolute value of value is greater than 0.5
		//return number rounded up or down
		//depending on whether it's positive or negative
		if (abs(modf(value, &real)) >= 0.5) {
			returnValue = value >= 0 ? ceil(value) : floor(value);
		} else {
			returnValue = value < 0 ? ceil(value) : floor(value);
		}

		return (int)returnValue;
	}

	uint32 pixelOffset(vec2 p, uint16 width_)
	{
		return (roundToInt(p.i) + roundToInt(p.j) * width_) * 4;
	}

	float parse(std::string str)
	{
		std::stringstream conv(str);

		float value = 0;
		conv >> value;

		return value;
	}

	//--- returns a value between 0 and 1
	float linearStep( float start, float stop, float value )
	{
		float step = clamp( start, stop, value );

		return (step - start) / (stop - start);
	}

	ooe::vec2 lerp(ooe::vec2 p0, ooe::vec2 p1, float s)
	{
		return (s == 0) ? p0 : (s == 1) ? p1 :
			(p0 * (1-s) + p1 * s);
	}

	float clamp( float min, float max, float value )
	{
		//return value-> value:[min, max]

		return (value < min) ? min : (value > max) ? max : value;
	}

}