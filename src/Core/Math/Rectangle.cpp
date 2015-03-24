#include "Rectangle.h"
#include "Utilities.hpp"
#include <algorithm>

namespace ooe
{
	Rectangle::Rectangle(int l, int t, int w, int h):
		left(l), top(t), width(w), height(h)
	{
	}

	void Rectangle::Clipto(const Rectangle &rec)
	{
		auto right = left + width;
		auto bottom = top + height;
		auto otherRight = rec.left + rec.width;
		auto otherBottom = rec.top + rec.height;

		left = std::max(rec.left, left);	
		top = std::max(rec.top, top);
		right = std::min(otherRight, right);
		bottom = std::min(otherBottom, bottom);

		width = std::max(0, right - left);
		height = std::max(0, bottom - top);
	}

	bool Rectangle::completelyInside(const Rectangle& otherRec) const
	{
		auto right = left + width;
		auto bottom = top + height;
		auto otherRight = otherRec.left + otherRec.width;
		auto otherBottom = otherRec.top + otherRec.height;

		return (left > otherRec.left && 
			top > otherRec.top && 
			right < otherRight && 
			bottom < otherBottom); 
	}

	bool Rectangle::completelyOutside(const Rectangle& otherRec) const
	{
		auto right = left + width;
		auto bottom = top + height;
		auto otherRight = otherRec.left + otherRec.width;
		auto otherBottom = otherRec.top + otherRec.height;

		return (right < otherRec.left || 
			bottom < otherRec.top ||
			left > otherRight ||
			top > otherBottom);
	}

	void Rectangle::Translate(int i, int j)
	{
		left += i;
		top += j;
	}

	bool Rectangle::operator==(Rectangle& other)
	{
		return (left == other.left &&
			width == other.width &&
			top == other.top && 
			height == other.height);
	}

	bool Rectangle::operator<(const Rectangle& other) const
	{
		return (width < other.width &&
			height < other.height);
	}

	bool Rectangle::operator>(const Rectangle& other) const
	{
		return (width > other.width &&
			height > other.height);
	}

	bool Rectangle::operator>=(const Rectangle& other) const
	{
		return (width >= other.width &&
			height >= other.height);
	}

	bool Rectangle::operator<=(const Rectangle& other) const
	{
		return (width <= other.width &&
			height <= other.height);
	} 

	Rectangle& Rectangle::operator/(int rhs)
	{
		width /= rhs;
		height /= rhs;

		return *this;
	}

	Rectangle& Rectangle::operator*(int rhs)
	{
		width *= rhs;
		height *= rhs;

		return *this;
	}

	Rectangle& Rectangle::operator+(int rhs)
	{
		width += rhs;
		height += rhs;

		return *this;
	}

	Rectangle& Rectangle::operator-(int rhs)
	{
		width -= rhs;
		height -= rhs;

		return *this;
	}

	Rectangle Rectangle::operator-(const Rectangle& other) const
	{
		return Rectangle(left - other.left,
			top - other.top, 
			width - other.width, 
			height - other.height);
	}

	Rectangle Rectangle::operator+(const Rectangle& other) const
	{
		return Rectangle(left + other.left, 
			top + other.top,
			width + other.width, 
			height + other.height);
	}

}