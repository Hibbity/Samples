/*
Author: Ryan Kirschman
Date: 4/15/2015

This is the header for the Vector3 class.
The Vector3 class stores 3 values for x, y, and z, as well as the length of the mathematical vector.
Two vectors can be added together and subtracted. You may perform the Dot Product as well as Cross Product.
A Vector3 can be multiplied or divided by a float to be scaled.
*/

#pragma once

namespace Math {
	class Vector3 {
	public:
		//static const unit Vectors
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Forward;

		//constructors
		Vector3();
		Vector3(float i_x, float i_y, float i_z);
		Vector3(const Vector3 &otherVec);

		//destructor
		~Vector3();

		// Getters
		inline float X() const, Y() const, Z() const, Length() const, LengthSqr() const;

		//Setters
		inline void X(const float x), Y(const float y), Z(const float z);

		// Normalizers
		inline Vector3 CreateNormalized();
		inline void Normalize();

		// Operators
		// Addition
		inline Vector3 operator +(const Vector3& rhs) const;
		inline Vector3& operator +=(const Vector3& rhs);

		// Subtraction
		inline Vector3 operator -(const Vector3& rhs) const;
		inline Vector3& operator -=(const Vector3& rhs);

		// Multiplication
		inline Vector3 operator *(const float rhs) const;
		inline Vector3& operator *=(const float rhs);
		inline friend Vector3 operator *(const float lhs, const Vector3& rhs);

		// Division
		inline Vector3 operator /(const float rhs) const;
		inline Vector3& operator /=(const float rhs);

		// Dot product
		inline friend float Dot(const Vector3& lhs, const Vector3& rhs);
		// Cross product
		inline friend Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
		// Scale product
		inline friend Vector3 Scale(const Vector3& lhs, const Vector3& rhs);
		
		// Interpolation
		friend Vector3 Lerp(const Vector3& start, const Vector3& end, float percent);

	private:
		//Sets the Length. Only called internally
		void CalculateLength();

		//variables
		float _x, _y, _z, _length;
	};

} //namespace Math