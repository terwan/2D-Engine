//
//	-Header file for the Rectangle Class which provides a Rectangle type
//	
//	-> Functions:
//		-> +Clipto(rectangle)
//		-> +completelyInside(rectangle)
//		-> +Outside(rectangle)
//		-> +Translate(i, j)
//		-> +getWidth/getHeight()

#pragma once
#include "Vector2D.h"

namespace ooe
{
	struct Rectangle
	{
		Rectangle(int left =0, int top =0, int width =0, int height =0);

		//Clip the edges of this rect onto that of other
		void Clipto(const Rectangle &rec);

		bool completelyInside(const Rectangle&) const;

		bool completelyOutside(const Rectangle&) const;

		//Shift the edges of this rect by the parameters i and j
		void Translate(int x, int y);

		//Test whether two recs are the exact same
		bool operator==(Rectangle& other);

		//Check whether another rec is larger or smaller than this
		bool operator<(const Rectangle& other) const;
		bool operator>(const Rectangle& other) const;
		bool operator>=(const Rectangle& other) const;
		bool operator<=(const Rectangle& other) const;

		//Manipulate the size of rec
		Rectangle& operator/(int rhs);
		Rectangle& operator*(int rhs);
		Rectangle& operator+(int rhs);
		Rectangle& operator-(int rhs);

		//Compute a third rec from the value of two
		Rectangle operator-(const Rectangle& other) const;
		Rectangle operator+(const Rectangle& other) const;

		int left, top, width, height;
	}; 
}