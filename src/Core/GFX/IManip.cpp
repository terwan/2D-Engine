#include "IManip.h"

namespace ooe
{

	void IManip::RemoveColour(uchar* source, int i, int j, Channel c)
	{
		switch(c) 
		{
		case kRed:
			Red(source, i, j);
			break;
		case kBlue:
			Blue(source, i, j);
			break;
		case kGreen:
			Green(source, i, j);
			break;
		}
	}

	void IManip::ColourInverse(uchar* source, int i, int j)
	{	
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				source[kRed] = (255 - source[kRed]);
				source[kGreen] = (255 - source[kGreen]);
				source[kBlue] = (255 - source[kBlue]);

				source += 4;
			}	
		}
	}
	
	void IManip::Greyscale(uchar* source, int i, int j)
	{
		uchar grey;

		//Set value for each colour channel, for each iteration, to a shade of grey
		//Define an equation which will cause a color channel to create a shade of grey
		//Assign the values of all channels to this color 'grey's
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				grey = (uchar)(pow(
					(pow(source[kRed], 2.2f) * 0.299) +
					(pow(source[kGreen], 2.2f) * 0.587) + 
					(pow(source[kBlue], 2.2f) * 0.114), 1/2.2f));

				source[kRed] = grey;
				source[kGreen] = grey;
				source[kBlue] = grey;

				source += 4;
			}
		}
	}

	void IManip::Sepia(uchar* source, int i, int j)
	{
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				source[kRed] = (uchar)((source[kRed] * 0.393) +
					(source[kGreen] * 0.769) +
					(source[kBlue] * 0.189));

				source[kGreen] = (uchar)((source[kRed] * 0.349) +
					(source[kGreen] * 0.686) +
					(source[kBlue] * 0.168));

				source[kBlue] = (uchar)((source[kRed] * 0.272) +
					(source[1] * 0.534) + 
					(source[kBlue] * 0.131));

				//Set value of pixels at position(count) to 1 if vaue is greater than 1
				//Since 3 values are being added together to make one, there are possibilities
				//	that the result will be greater than the threshold value (1) which cause Model
				//	distortions.

				if(source[kRed] > 255){
					source[kRed] = 255;
				}
				if(source[kGreen] > 255){
					source[kGreen] = 255;
				}
				if(source[kBlue] > 255){
					source[kBlue] = 255;
				}

				source += 4;
			}
		}
	}

	void IManip::Red(uchar* source, int i, int j) 
	{
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				source[kRed] = 0;

				source +=4;
			}
		}
	}

	void IManip::Green(uchar* source, int i, int j) 
	{
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				source[kGreen] = 0;

				source +=4;
			}
		}
	}

	void IManip::Blue(uchar* source, int i, int j)
	{
		for (int i = 0; i < j; ++i) {
			for (int j = 0; j < i; ++j) {
				source[kBlue] = 0;

				source +=4;
			}
		}
	} 
}