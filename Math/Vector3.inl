/*
Author: Ryan Kirschman
Date: 4/15/2015

An inline file used to define my inline functions for the Vector3 class.
*/

#include "Vector3.h"

namespace Math
{
	// Constructors
	Vector3::Vector3() :
		_x(0),
		_y(0),
		_z(0),
		_length(0)
	{
	}
	Vector3::Vector3(float x, float y, float z) :
		_x(x),
		_y(y),
		_z(z)
	{
		CalculateLength();
	}

	Vector3::Vector3(const Vector3 &i_Vector) :
		_x(i_Vector._x),
		_y(i_Vector._y),
		_z(i_Vector._z),
		_length(i_Vector._length)
	{
	}

	// Getters
	inline float Vector3::X() const { return _x; }
	inline float Vector3::Y() const { return _y; }
	inline float Vector3::Z() const { return _z; }
	inline float Vector3::Length() const
	{
		return _length;
	}
	inline float Vector3::LengthSqr() const
	{
		return _length * _length;
	}

	//Setters
	inline void Vector3::X(const float x)
	{
		_x = x;
		CalculateLength();
	}
	inline void Vector3::Y(const float y)
	{
		_y = y;
		CalculateLength();
	}
	inline void Vector3::Z(const float z)
	{
		_z = z;
		CalculateLength();
	}

	// Normalizers
	inline Vector3 Vector3::CreateNormalized()
	{
		return *this / this->Length();
	}
	inline void Vector3::Normalize()
	{
		*this /= this->Length();
	}

	// Operators
	// Addition
	inline Vector3 Vector3::operator +(const Vector3& rhs) const
	{
		return Vector3(_x + rhs._x, _y + rhs._y, _z + rhs._z);
	}
	inline Vector3& Vector3::operator +=(const Vector3& rhs)
	{
		_x += rhs._x;
		_y += rhs._y;
		_z += rhs._z;
		CalculateLength();
		return *this;
	}

	// Subtraction
	inline Vector3 Vector3::operator -(const Vector3& rhs) const
	{
		return Vector3(_x - rhs._x, _y - rhs._y, _z - rhs._z);
	}
	inline Vector3& Vector3::operator -=(const Vector3& rhs)
	{
		_x -= rhs._x;
		_y -= rhs._y;
		_z -= rhs._z;
		CalculateLength();
		return *this;
	}

	// Multiplication
	inline Vector3 Vector3::operator *(const float rhs) const
	{
		return Vector3(_x * rhs, _y * rhs, _z * rhs);
	}
	inline Vector3& Vector3::operator *=(const float rhs)
	{
		_x *= rhs;
		_y *= rhs;
		_z *= rhs;
		CalculateLength();
		return *this;
	}
	inline Vector3 operator *(const float lhs, const Vector3& rhs)
	{
		return lhs * rhs;
	}

	// Division
	inline Vector3 Vector3::operator /(const float rhs) const
	{
		const float recip = 1.0f / rhs;
		return Vector3(_x * recip, _y * recip, _z * recip);
	}
	inline Vector3& Vector3::operator /=(const float rhs)
	{
		const float recip = 1.0f / rhs;
		_x *= recip;
		_y *= recip;
		_z *= recip;
		return *this;
	}

	// Dot product
	inline float Dot(const Vector3& lhs, const Vector3& rhs)
	{
		return (lhs._x * rhs._x) + (lhs._y * rhs._y) + (lhs._z * rhs._z);
	}
	// Cross product
	inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(	(lhs._y * rhs._z) - (lhs._z * rhs._y), 
						(lhs._z * rhs._x) - (lhs._x * rhs._z), 
						(lhs._x * rhs._y) - (lhs._y * rhs._x) );
	}
	// Scale product
	inline Vector3 Scale(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs._x * rhs._x, lhs._y * rhs._y, lhs._z * rhs._z);
	}
}