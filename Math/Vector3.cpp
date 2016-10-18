/*
Author: Ryan Kirschman
Date: 4/15/2015

This is the source file for the Vector3 class. 
I use it to define CalculateLength, as that needs the squareroot function found in math.h.
This keeps math.h out of being included into Vector3.h
I also define my static unit vectors here.
*/

#include "Vector3.h"

#include <math.h>
#include "Functions.h"

namespace Math
{
	//static const unit Vectors
	const Vector3 Vector3::Right	=	Vector3(1, 0, 0);
	const Vector3 Vector3::Up		=	Vector3(0, 1, 0);
	const Vector3 Vector3::Forward	=	Vector3(0, 0, 1);

	void Vector3::CalculateLength()
	{
		_length = sqrtf((_x * _x) + (_y * _y) + (_z * _z));
	}

	// Interpolation
	Vector3 Lerp(const Vector3& start, const Vector3& end, float percent)
	{
		return Vector3(Lerp(start._x, end._x, percent),
			Lerp(start._y, end._y, percent),
			Lerp(start._z, end._z, percent));
	}
}