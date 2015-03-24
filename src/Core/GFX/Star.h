#pragma once

#include "../Math/Vector2D.h"
#include "../Core.h"

namespace ooe
{
	class Star
	{
		friend class Graphics; 

		struct Vector3D : public Vector2D
		{
			double k;

			Vector3D() : k(0.0) {}
		};

	public:
		//init star class
		void create(int starCount = 500, int eyeDist = 100);

		//Check whether star array has been populated
		bool isCreated() const;

		//Starfield effect with stars moving toward screen
		void GenerateStars(uint16 screen_width, uint16 screen_height, HAPI_TColour = HAPI_TColour(0,0,0));

		int starCount() const { return star_count_; }
		int eyeDistance() const { return eye_distance_; }

	private:
		void setSCount(int count);
		void setEyeDist(int distance);

		Star();
		Star(Star& copy);
		Star& operator=(const Star& copy); 
		void copyStar(const Star& copy);


		int star_count_;
		int eye_distance_;
		std::vector<Vector3D> stars_;
	}; 
}