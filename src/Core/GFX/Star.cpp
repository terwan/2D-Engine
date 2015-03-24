#include "Star.h"
#include "../Math/Utilities.hpp"

namespace ooe
{

	Star::Star() : star_count_(0), eye_distance_(0)
	{
	}


	Star::Star(Star& copy)
	{
		copyStar(copy);
	}


	void Star::create(int count, int distance)
	{
		setSCount(count);
		setEyeDist(distance);
	}


	bool Star::isCreated() const
	{
		if (stars_.empty()) return false;

		return true;
	}


	void Star::GenerateStars(uint16 screen_width, uint16 screen_height, HAPI_TColour colour)
	{

		if (!isCreated()) return;
		else if ((screen_width * screen_height) <= 0) return;

		int Cx = screen_width / 2;
		int Cy = screen_height / 2;

		/*
		* Loops through array of Star
		* sets i, j, z values
		* evuluates screen position
		* copies to screen buffer
		*/
		for (int idx = 0; idx < star_count_; ++idx)
		{
			if (stars_[idx].k <= 0) //Regenerate Star once out of bounds
			{
				stars_[idx].i = (double)(rand() % screen_width);
				stars_[idx].j = (double)(rand() % screen_height);
				stars_[idx].k = (double)(rand() % 100);
			}

			double Px = stars_[idx].i;
			double Py = stars_[idx].j;
			double Pz = stars_[idx].k;

			double Sx = ((eye_distance_ * (Px-Cx)) / (eye_distance_+Pz)) + Cx;
			double Sy = ((eye_distance_ * (Py-Cy)) / (eye_distance_+Pz)) + Cy;

			uchar* offset = HAPI->GetScreenPointer() + pixelOffset(vec2(Sx, Sy), screen_width);

			if (colour.red & colour.green & colour.blue) {
				setPixelColour(offset, colour);

			} else {
				setPixelColour(offset, HAPI_TColour(rand() % 255, rand() % 255, rand() % 255));
			}

			stars_[idx].k -= 0.05f; //Decrements Z to give a 3d effect
		}
	}

	void Star::setSCount(int count)
	{
		count = std::max(1, count);
		star_count_ = count;
		stars_.resize(star_count_);
	}


	void Star::setEyeDist(int distance)
	{
		distance = std::max(1, distance);
		eye_distance_ = distance;
	}


	Star& Star::operator=(const Star& copy)
	{
		if (this != &copy) copyStar(copy);
		return *this;
	}


	void Star::copyStar(const Star& copy)
	{
		eye_distance_ = copy.eye_distance_;
		star_count_ = copy.star_count_;	
		stars_ = copy.stars_;
	} 
}