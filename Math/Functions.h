/*
Author: Ryan Kirschman
Date: 2/12/2015

This header file contains the declarations for various mathematical functions.
These functions are Global within in Math namespace.

Functions include different interpolation functions including various easing functions.
It also includes many functions for modular spaces, such as angles.
*/

#pragma once

// Forward declaration
namespace Math
{
	class Vector3;
}

namespace Math
{
	/******    Approx.     ******/
	bool Close(float lhs, float rhs, float range = 0.01f); // Returns true if the two values are within a range of each other

	/******   Logarithm    ******/
	float LogBase(float value, float base); // Returns the log of the value given the base

	/******      Misc      ******/
	float DeadZone(float value, float deadZone); // Returns 0 if value is less than deadZone
	float NormalizeToRange(float value, float min, float max); // Normalizes a value to the range min-max.
	float ModularRange(float value, float min, float max); // Creates a modular space between min and max, and then places value into space.
	float ModularClamp(float value, float modMin, float modMax, float clampMin, float clampMax); // Clamps value between two numbers within a modular set of values

	/******  Interpolation   ******/
	float Lerp(float start, float end, float percent); // Linearly interpolates between the start and end given a percentage of the way through
	float ModLerp(float start, float end, float percent, float modMin, float modMax); // Linearly interpolates across modular space, such as with angles

	/****** Easing Functions ******/
	// Note: Easing functions are a way to smoothly interpolate between two points, typically not linearly.
	// Sinosuidal Easing
	float EaseInSin(float start, float end, float percent);
	float EaseOutSin(float start, float end, float percent);
	float EaseInOutSin(float start, float end, float percent);
	Vector3 EaseInSin(Vector3 start, Vector3 end, float percent);
	Vector3 EaseOutSin(Vector3 start, Vector3 end, float percent);
	Vector3 EaseInOutSin(Vector3 start, Vector3 end, float percent);

	// Circular Easing (square root)
	float EaseInCirc(float start, float end, float percent);
	float EaseOutCirc(float start, float end, float percent);
	float EaseInOutCirc(float start, float end, float percent);
	Vector3 EaseInCirc(Vector3 start, Vector3 end, float percent);
	Vector3 EaseOutCirc(Vector3 start, Vector3 end, float percent);
	Vector3 EaseInOutCirc(Vector3 start, Vector3 end, float percent);

	// Quadratic Easing
	float EaseInQuad(float start, float end, float percent);
	float EaseOutQuad(float start, float end, float percent);
	float EaseInOutQuad(float start, float end, float percent);
	Vector3 EaseInQuad(Vector3 start, Vector3 end, float percent);
	Vector3 EaseOutQuad(Vector3 start, Vector3 end, float percent);
	Vector3 EaseInOutQuad(Vector3 start, Vector3 end, float percent);

}