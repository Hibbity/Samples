/*
Author: Ryan Kirschman
Date: 2/12/2015

This source file contains the defintions for the functions declared in Functions.h
*/

#include "Functions.h"

#include <math.h>
#include "Constants.h"
#include "Vector3.h"

namespace Math
{
	/******    Approx.     ******/
	// Returns true if the two values are within a range of each other
	bool Close(float lhs, float rhs, float range)
	{
		if (abs(rhs - lhs) < abs(range))
		{
			return true;
		}

		return false;
	}

	/******   Logarithm    ******/
	// Returns the log of the value given the base
	float LogBase(float value, float base)
	{
		return logf(value) / logf(base);
	}

	/******      Misc      ******/
	// Returns 0 if value is less than deadZone
	float DeadZone(float value, float deadZone)
	{
		if (abs(value) < deadZone)
		{
			return 0;
		}
		return value;
	}

	// Normalizes a value to the range min-max. 
	float NormalizeToRange(float value, float min, float max)
	{
		if (min == max)
		{
			// min should never be equal to max since we need a range.
			// if it is equal, return INFINITY as that is a value not able to be returned by normalization
			return INFINITY;
		}

		return (value - min) / (max - min);
	}

	// Creates a modular space between min and max, and then places value into space.
	float ModularRange(float value, float min, float max)
	{
		float range = max - min;
		return fmodf(value + range - min, range) + min;
	}

	// Clamps value between two numbers within a modular set of values
	// This is useful if you want to clamp an angle as angles are modular
	float ModularClamp(float value, float modMin, float modMax, float clampMin, float clampMax)
	{
		// Mod all of our values by the range of our modular space.
		float modRange = modMax - modMin;
		float modValue = ModularRange(value, modMin, modMax);
		float modClampMin = ModularRange(clampMin, modMin, modMax);
		float modClampMax = ModularRange(clampMax, modMin, modMax);

		// Is the min less than the max (eg. min of 90 and max of 270 as opposed to min of 270 (-90) and max of 90).
		if (modClampMin < modClampMax)
		{
			if (modValue < modClampMin)
			{
				return modClampMin;
			}
			if (modValue > modClampMax)
			{
				return modClampMin;
			}
			return modValue;
		}
		if (modClampMin > modClampMax)
		{
			// If we're greater than the min OR less than the max, then it's within range.
			// This uses OR not AND because it's modular and the min is greater than the max.
			if (modValue > modClampMin || modValue < modClampMax)
			{
				return modValue;
			}

			// Is value closer to the min or the max. Which does it clamp to since it's modular?
			if (abs(modValue - modClampMin) < abs(modValue - modClampMax))
			{
				return modClampMin;
			}

			return modClampMax;
		}
		return modClampMin;
	}

	/******  Interpolation   ******/
	// Linearly interpolates between the start and end given a percentage of the way through
	float Lerp(float start, float end, float percent)
	{
		return start + percent * (end - start);
	}

	// Linearly interpolates across modular space, such as with angles
	float ModLerp(float start, float end, float percent, float modMin, float modMax)
	{
		float modRange = modMax - modMin;
		float modStart = ModularRange(start, modMin, modMax);
		float modEnd = ModularRange(end, modMin, modMax);

		float distance = modEnd - modStart;
		if (abs(distance) < modRange * 0.5f)
		{
			// If going from the end to the start is less than half of our modular space's size
			// then moving directly from start to end is the shortest path. Just normal interpolation (implement our own instead of calling Lerp so we don't calculate distance twice).
			return modStart + percent * distance;
		}
		
		// If we reach this point, the shortest path is to go "backwards" (cut through the modular break point).
		// We can easily linearly interpolate between the two so long as we 
		if (modEnd > modStart)
		{
			modEnd -= modRange;
		}
		else
		{
			modEnd += modRange;
		}
		return ModularRange(Lerp(modStart, modEnd, percent), modMin, modMax);
	}

	//****** Easing Functions ******/
	// Note: Easing functions are a way to smoothly interpolate between two points, typically not linearly.
	// Sinosuidal Easing
	float EaseInSin(float start, float end, float percent)
	{
		return Lerp(start, end, 1 - cosf((percent)* (Pi)));
	}
	float EaseOutSin(float start, float end, float percent)
	{
		return Lerp(start, end, sinf((percent)* (Pi)));
	}
	float EaseInOutSin(float start, float end, float percent)
	{
		return Lerp(start, end, 0.5f + 0.5f * cosf((percent - 0.5f) * (Pi)));
	}
	Vector3 EaseInSin(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, 1 - cosf((percent)* (Pi)));
	}
	Vector3 EaseOutSin(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, sinf((percent)* (Pi)));
	}
	Vector3 EaseInOutSin(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, 0.5f + 0.5f * cosf((percent - 0.5f) * (Pi)));
	}

	// Quadratic Easing
	float EaseInCirc(float start, float end, float percent)
	{
		return Lerp(start, end, 1 - sqrtf(1 - percent * percent));
	}
	float EaseOutCirc(float start, float end, float percent)
	{
		return Lerp(start, end, sqrtf(1 - percent * percent));
	}
	float EaseInOutCirc(float start, float end, float percent)
	{
		if (percent < 0.5f)
		{
			percent *= 2;
			return Lerp(start, end, 0.5f * (1 - sqrtf(1 - percent * percent)));
		}
		percent = percent * 2 - 2;
		return Lerp(start, end, 0.5f * (1 + sqrtf(1 - percent * percent)));
	}
	Vector3 EaseInCirc(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, 1 - sqrtf(1 - percent * percent));
	}
	Vector3 EaseOutCirc(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, sqrtf(1 - percent * percent));
	}
	Vector3 EaseInOutCirc(Vector3 start, Vector3 end, float percent)
	{
		percent *= 2;
		if (percent < 1.0f)
		{
			return Lerp(start, end, 0.5f * (1 - sqrtf(1 - percent * percent)));
		}
		percent -= 2;
		return Lerp(start, end, 0.5f * (1 + sqrtf(1 - percent * percent)));
	}

	// This is a function for a new interpolation that eases in and out quadratically
	float EaseInQuad(float start, float end, float percent)
	{
		return Lerp(start, end, percent * percent);
	}
	float EaseOutQuad(float start, float end, float percent)
	{
		return Lerp(start, end, percent * (2 - percent));
	}
	float EaseInOutQuad(float start, float end, float percent)
	{
		percent *= 2;
		if (percent < 1)
		{
			return Lerp(start, end, 0.5f * percent * percent);
		}
		percent -= 1;
		return Lerp(start, end, 0.5f * (1 - percent * (percent - 2)));
	}
	Vector3 EaseInQuad(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, percent * percent);
	}
	Vector3 EaseOutQuad(Vector3 start, Vector3 end, float percent)
	{
		return Lerp(start, end, percent * (2 - percent));
	}
	Vector3 EaseInOutQuad(Vector3 start, Vector3 end, float percent)
	{
		percent *= 2;
		if (percent < 1)
		{
			return Lerp(start, end, 0.5f * percent * percent);
		}
		percent -= 1;
		return Lerp(start, end, 0.5f * (1 - percent * (percent - 2)));
	}
}