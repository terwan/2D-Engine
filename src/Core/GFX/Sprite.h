#pragma once

#include "../Math/Rectangle.h"
#include "../Core.h"

namespace ooe
{

	class Sprite
	{
		friend class Graphics;

	public:
		const Sprite& operator=(const Sprite& copy); 
		Sprite(const Sprite& copy); //TODO: Fix error when putting these as private


	private:
		//Clip edges of texture to destination, clamp position and return the new texture
		Rectangle clipEdges(vec2& position, const Rectangle& destination_rectangle);

		const Rectangle& dimensions() const { return source_dimension; }

		uint32 frames() const { return frames_; }

		bool loadSprite(const std::string& name);

		//Transparent Blit and Frame selection support
		void blit(vec2 position, uchar* destination, uint16 screen_width, uint16 screen_height, 
			Rectangle destination_rectangle, Rectangle frame_dimensions, uint16 frame_number);

		//Fast, Non transparent blitting
		void quickBlit(vec2 position, uchar *destination, uint16 screen_width, uint16 screen_height, Rectangle destination_rectangle);

		//sets colours of pixels for transparent effect; Used to implement Blit and transparentBlit
		void Transparent(uchar* source, uchar* destination, uint16 screen_width, uint16 screen_height, Rectangle source_dimensions) const;

		Sprite();
		void copySprite(const Sprite& copy);


		uint16 frame_;
		uint32 frames_;
		Rectangle source_dimension;
		uchar* texture_data_;
		std::string texture_name_;
	};

}