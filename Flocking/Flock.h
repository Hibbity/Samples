/*
Author: Ryan Kirschman
Date: 3/30/2016

The Flock Component is an IComponent used to simulate flocking behavior.
It communicates with its GameObject's Rigidbody, which handles the physics of the movement.
The GameObject stores the Object's Position, which is used to separate and group objects that are flocking.

This Sample Code is from my own engine written in C++. It uses my own custom SmartPointer,
a custom cVector class for a mathematical vector, as well as the Vector container from the Standard Library.
*/

#pragma once

#include "IComponent.h"

// Forward Declaration
namespace Physics
{
	class Rigidbody;
}

namespace Component
{
	class Flock : public Component::IComponent
	{
	public:
		static std::vector<SmartPointer<World::GameObject>> FlockingList;

		// Static function to create an instance of the class. Used to return a SmartPointer and initialize instead of calling constructor directly.
		static SmartPointer<Component::IComponent> Create(SmartPointer<World::GameObject> i_pActor);
		
		~Flock();

		void Update(float i_TimeSinceLastFrame);

		SmartPointer<Physics::Rigidbody> m_Rigidbody;		

		// Getters and Setters
		float MaxSpeedSqr() { return m_MaxSqrSpeed; }
		float MaxSpeed() { return sqrtf(m_MaxSqrSpeed); }
		void MaxSpeed(float i_speed) { m_MaxSqrSpeed = i_speed * i_speed; }

		// Public variables
		// These are made public so that they can be changed quickly and efficiently
		float neighborDistanceSqr;
		float separationWeight;
		float alignmentWeight;
		float cohesionWeight;

	private:
		Flock(SmartPointer<World::GameObject> i_pActor);

		std::vector<SmartPointer<World::GameObject>> neighbors;

		// Store the max speed squared.
		// Used to make sure the flocking object is not going too quickly
		float m_MaxSqrSpeed;
	};
}