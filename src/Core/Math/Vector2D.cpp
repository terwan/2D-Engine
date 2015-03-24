#include "Vector2D.h"

namespace ooe
{

	double Vector2D::cross(const Vector2D &other) const
	{
		return dot(other) / (length() * other.length());
	} 

	double Vector2D::distance(const Vector2D& other) const
	{
		auto new_x = pow(other.i - i, 2);
		auto new_y = pow(other.j - j, 2);

		return sqrt(new_x + new_y);
	}

	double Vector2D::dot(const Vector2D& other) const
	{
		return i * other.i + j * other.j;
	}

	double Vector2D::length() const
	{
		return sqrt(i * i + j * j);
	}

	double Vector2D::lenSqr() const
	{
		return i * i + j * j;
	}

	Vector2D Vector2D::unit()
	{
		i /= length();
		j /= length();

		return *this;
	}

#pragma region Overloaded Operators
	bool Vector2D::operator==(Vector2D& other) const
	{
		return (i == other.i && j == other.j);
	}

	bool Vector2D::operator!=(Vector2D& other) const
	{
		return (i != other.i || j != other.j);
	}

	bool Vector2D::operator<(Vector2D& other) const
	{
		return (i < other.i && j < other.j);
	}

	bool Vector2D::operator>(Vector2D& other) const
	{
		return (i > other.i && j > other.j);
	}

	bool Vector2D::operator<=(Vector2D& other) const
	{
		return (i <= other.i && j <= other.j);
	}

	bool Vector2D::operator>=(Vector2D& other) const
	{
		return (i >= other.i && j >= other.j);
	}

	Vector2D Vector2D::operator+(const Vector2D &rhs) const
	{
		return Vector2D(i + rhs.i, j + rhs.j);
	}

	Vector2D Vector2D::operator-(const Vector2D &rhs) const
	{
		return Vector2D(i - rhs.i, j - rhs.j);
	}

	Vector2D& Vector2D::operator+=(const Vector2D &rhs)
	{
		i += rhs.i;
		j += rhs.j;

		return *this;
	}

	Vector2D& Vector2D::operator-=(const Vector2D &rhs)
	{
		i -= rhs.i;
		j -= rhs.j;

		return *this;
	}

	Vector2D Vector2D::operator+(double rhs) const
	{
		return Vector2D(i + rhs, j + rhs);
	}

	Vector2D Vector2D::operator-(double rhs) const
	{
		return Vector2D(i - rhs, j - rhs);
	}

	Vector2D Vector2D::operator*(double rhs) const
	{
		return Vector2D(i * rhs, j * rhs);
	}

	Vector2D& Vector2D::operator+=(double rhs)
	{
		i += rhs;
		j += rhs;

		return *this;
	}

	Vector2D& Vector2D::operator-=(double rhs)
	{
		i -= rhs;
		j -= rhs;

		return *this;
	}

	Vector2D& Vector2D::operator*=(double rhs)
	{		
		i *= rhs;
		j *= rhs;

		return *this;
	}
#pragma endregion
}