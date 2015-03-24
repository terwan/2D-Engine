#pragma once

#include "../Core.h"

namespace ooe
{

	class IManip //TODO: Develop this class more. Possibly split off sprite data from sprite class into it's own class so i can manipulate it
	{
		enum Channel { kRed, kGreen, kBlue, kAlpha };
	public:
		IManip(){}

		void RemoveColour(uchar* source, int i, int j, Channel c);
		void ColourInverse(uchar* source, int i, int j);
		void Greyscale(uchar* source, int i, int j);
		void Resize(uchar* source, int i, int j);
		void Sepia(uchar* source, int i, int j);

		//	void Opacity(float opacity);
		//	void Dither(uchar* dither); 
		//	void Sharpen(uchar* Sharpen); 
		//	void Emboss(uchar* emboss); 
		//	void FindEdges(uchar* fEdges); 
		//	void const Blur(uchar* blur); 
		//	void motionBlur(uchar* mblur);
		//	void LinearBlur(uchar* lblur);
		//	void RadialBlur(uchar* rblur);
	
	private:
		void Red(uchar* source, int i, int j);
		void Green(uchar* source, int i, int j);
		void Blue(uchar* source, int i, int j);

		int pixel_count_;
	}; 
}