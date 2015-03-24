//
//	-Header file for the Star Class which provides a 2D Vector Type
//	
//	-> Functions:
//		-> +length()
//		-> +lenSqr()
//		-> +unit()
//		-> +dot(vector)
//		-> +cross(vector)

#pragma once

#include <cmath>

namespace ooe
{
	class Vector2D
	{		
	public:
		double i, j;

		Vector2D(double _i = 0.f, double _j = 0.f) : i(_i),j(_j) {}

		//Returns cos(0) angle of the cross product of 2 vectors
		double cross(const Vector2D &other) const;

		//return the dot product of 2 vectors
		double dot(const Vector2D& other) const;

		//Length of vector
		double length() const;
		double lenSqr() const;

		//normalize the member variables of this vector
		Vector2D unit();

		//distance between two vectors
		double distance(const Vector2D& other) const;

		//Check Equality of vector sizes
		bool operator==(Vector2D& other) const;
		bool operator!=(Vector2D& other) const;
		bool operator<(Vector2D& other) const;
		bool operator>(Vector2D& other) const;
		bool operator<=(Vector2D& other) const;
		bool operator>=(Vector2D& other) const;

		//Overloaded Arithemtic operators
		Vector2D operator+(const Vector2D &rhs) const;
		Vector2D operator-(const Vector2D &rhs) const;
		Vector2D& operator+=(const Vector2D &rhs);
		Vector2D& operator-=(const Vector2D &rhs);
		Vector2D operator+(double rhs) const;
		Vector2D operator-(double rhs) const;
		Vector2D operator*(double rhs) const;
		Vector2D& operator+=(double rhs);
		Vector2D& operator-=(double rhs);
		Vector2D& operator*=(double rhs);
	};

	typedef Vector2D vec2;
}