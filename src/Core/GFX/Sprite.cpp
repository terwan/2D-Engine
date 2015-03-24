#include "Sprite.h"
#include "../Math/Utilities.hpp"

namespace ooe
{

	Sprite::Sprite() : frame_(0), frames_(0)
	{
	}

	Sprite::Sprite(const Sprite& copy)
	{
		copySprite(copy);
	}


	Rectangle Sprite::clipEdges(vec2& position, const Rectangle& destRec)
	{
		Rectangle textureRec = source_dimension;

		//Move texture to screen space
		textureRec.Translate((int)position.i, (int)position.j);

		//Clip texture to the screen and move back to source space
		textureRec.Clipto(destRec);
		textureRec.Translate(-(int)position.i, -(int)position.j);

		//Clamp negative i and j values so that destination vec2 isn't outside of screen memory array
		position.i = std::max(0.0, position.i);
		position.j = std::max(0.0, position.j);

		return textureRec;
	}


	bool Sprite::loadSprite(const std::string& name)
	{
		int width, height;

		if (HAPI->LoadTexture(name, &texture_data_, &width, &height)) {
			texture_name_ = name;
			source_dimension.width = width;
			source_dimension.height = height;
			return true;
		}

		return false;
	}


	void Sprite::blit(vec2 position, uchar* destination, uint16 screen_width, uint16 screen_height, 
		Rectangle destRec, Rectangle frame_dimen, uint16 frame_number)
	{
		Rectangle textureRec = clipEdges(position, destRec);

		uint16 horiFrames, vertFrames;

		//Assign texture and frame_number valuess
		if (frame_dimen.width * frame_dimen.height > 0) {
			textureRec.width = frame_dimen.width;
			textureRec.height = frame_dimen.height;

			horiFrames = (uint16)ceil(source_dimension.width / frame_dimen.width);
			vertFrames = (uint16)ceil(source_dimension.height / frame_dimen.height);
			frames_ = vertFrames * horiFrames;
		}

		//Skip 'Frame finding' if texture is completely within/outside screen space
		if (textureRec.completelyOutside(destRec)) {
			return;
		} else if (textureRec.completelyInside(destRec) && frames_ == 0) {
			uchar* source_ptr = texture_data_;
			uchar *destination_ptr = destination + pixelOffset(position, screen_width);	

			Transparent(source_ptr, destination_ptr, screen_width, screen_height, source_dimension);
			return;
		}

		//Move textureRec around source texture to select which area of source rectangle is used during blit
		if (frame_number > 0 && frame_number <= frames_) {
			frame_number = frame_number - 1;
			uint16 j = (uint16)floor(frame_number / horiFrames);
			uint16 i = frame_number - (j * horiFrames);

			textureRec.Translate(i * frame_dimen.width, j * frame_dimen.height);
		}

		uchar *source_ptr = texture_data_ + pixelOffset(vec2(textureRec.left, textureRec.top), source_dimension.width);
		uchar *destination_ptr = destination + pixelOffset(position, screen_width);	

		Transparent(source_ptr, destination_ptr, screen_width, screen_height, textureRec);
	}


	void Sprite::quickBlit(vec2 position, uchar *destination, uint16 screen_width, uint16 screen_height, Rectangle destRec)
	{ 
		Rectangle textureRec = clipEdges(position, destRec);

		uchar* source_ptr = texture_data_ + pixelOffset(vec2(textureRec.left, textureRec.top), source_dimension.width);
		uchar *destination_ptr = destination + pixelOffset(position, screen_width);	

		uint16 height = std::min((uint16)textureRec.height, screen_height);
		uint16 width = std::min((uint16)textureRec.width, screen_width);

		for (uint16 i = 0; i < textureRec.height; ++i) 
		{ 
			memcpy(destination_ptr, source_ptr, textureRec.width * 4); 

			source_ptr += source_dimension.width * 4; 
			destination_ptr += screen_width * 4; 
		} 
	}


	void Sprite::Transparent(uchar* source, uchar* destination, uint16 screen_width, uint16 screen_height, Rectangle src_dimen) const
	{
		int endOfLineDestinationIncrement = (screen_width - src_dimen.width) * 4;
		int endOfLineSourceIncrement = (source_dimension.width - src_dimen.width) * 4;
		uint16 height = std::min((uint16)src_dimen.height, screen_height);
		uint16 width = std::min((uint16)src_dimen.width, screen_width);

		/*Loops through each pixel on screen and alters their colour(RGB) values based on a textures alpha value 			
		//		1) Move to the next line of pixels on the screen
		//		2) Increment through a line of pixels
		//		3) Set a byte 'alpha' to the value(a) stored in the 4th position of a loaded texture
		//		4) loop through the first 3 bytes of data(r,g,b) stored in a texil
		//		5) continue to next interation of loop if alpha is 0; screen data is preserved
		//		6) use texture data if alpha is 255; screen data because texture data
		//		7) Screen data is a blend between texture data and screen data	
		//		8) after every line of pixels(i), Increment Source and destination vec2ers so that they vec2 to the next line of texture data
		//		9) after every j, increment destination pntr so that it vec2s to the correct position below the previous texture	
		*/
		for (uint16 j = 0; j < height; ++j) {
			for (uint16 i = 0; i < width; ++i) {
				uchar alpha = source[3]; 

				for (uint16 idx = 0; idx < 3; ++idx) {
					if (alpha == 0) { 
						continue;

					} else if (alpha > 100) { 
						destination[idx] = source[idx];
					}
					destination[idx] = destination[idx]	+ ((alpha * (source[idx] - destination[idx])) >> 8);	
				}
				source += 4;
				destination += 4;
			}
			destination += endOfLineDestinationIncrement;
			source += endOfLineSourceIncrement;
		}
	}


	const Sprite& Sprite::operator=(const Sprite& copy)
	{
		if (this != &copy) copySprite(copy);
		return *this;
	}


	void Sprite::copySprite(const Sprite& copy)
	{
		frame_ = copy.frame_;
		frames_ = copy.frames_;
		source_dimension = copy.source_dimension;
		texture_data_ = copy.texture_data_;
		texture_name_ = copy.texture_name_;
	} 
}