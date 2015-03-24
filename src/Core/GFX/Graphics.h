#pragma once

#include "Star.h"
#include "Sprite.h"
#include "../Math/Utilities.hpp"

namespace ooe
{
	class Graphics
	{
	public:
		~Graphics();

		//Clear entire screen to a colour - defaults to black
		void clearColour(HAPI_TColour = HAPI_TColour(0,0,0));

		//draw texture to screen
		//id = id of sprite determined when sprite was loaded in - load() function
		void draw(vec2 position = 0, uint16 id = 0, Rectangle frame_dimen = 0, uint16 frame = 1);
		void quickdraw(vec2 position = 0, uint16 id = 0);

		//init the HAPI window 
		//Param1 = width; Param2 = height; Param3 = Toggle Fullscreen Mode
		bool init(uint16 width, uint16 height, bool fs = false);

		//load in texture data for further processing
		//Param1 = name of texture, param2 = id which will be assigned to texture
		//Error message displayed if texture load failed
		bool load(const std::string& name, uint16& id);

		Star& star();

		//Sprite Data
		const Rectangle& spriteDimensions(const uint16 id) const;

		//returns the Total Number of frames in a given texture
		uint32 spriteFrames(const uint16 id) const;

		static Graphics& getInstance();
		static uint16 width() { return width_; }
		static uint16 height() { return height_; }

	private:
		Star star_;
		std::vector<Sprite> sprites_;
		std::unique_ptr<uchar> pntr2screen_;

		//Hidden Constructor, copy constructor and assignment operator
		Graphics();
		const Graphics& operator=(const Graphics& rhs);
		Graphics(const Graphics& rhs);

		//Helper: Copy instance of one Graphics into another. NB: serves irrelvant purpose at the moment due to singleton
		void copyGraphics(const Graphics& rhs);

		static uint16 width_, height_;
		static bool instance_flag_;
		static Graphics* instance_;
	};

#define gfx Graphics::getInstance()
}
