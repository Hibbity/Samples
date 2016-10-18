/*
	Author: Ryan Kirschman
	Date: 3/30/2016

	This is the complementary cpp file for Flock.h
	I use the custom cVector class, which is a mathematical vector,
	as well as certain Mathematical constants found in "Math/Functions.h"
*/

#include "Flock.h"

#include "../GameObject.h"
#include "../../Physics/Rigidbody.h"
#include "Math/cVector.h"
#include "Math/Functions.h"

namespace Component 
{
	std::vector<SmartPointer<World::GameObject>> Flock::FlockingList;
	SmartPointer<IComponent> Flock::Create(SmartPointer<World::GameObject> i_pActor) 
	{
		SmartPointer<Flock> flocker = SmartPointer<Flock>(new Flock(i_pActor));
		if (flocker.HavePtr())
		{
			FlockingList.push_back(flocker->gameObject);
		}
		flocker->m_Rigidbody->Velocity(Math::cVector(rand() % 10 - 5, rand() % 10 - 5));

		SmartPointer<IComponent> comp;
		flocker.Cast(comp);
		return comp;
	}

	Flock::Flock(SmartPointer<World::GameObject> i_pActor)
	{
		gameObject = i_pActor;
		m_Rigidbody = i_pActor->Rigidbody();
		SmartPointer<IComponent> t_pointer = SmartPointer<IComponent>(this);
		World::ActorList->push_back(t_pointer);
		MaxSpeed(5);
	}

	Flock::~Flock() {
		if (!gameObject->isDead()) {
			gameObject.~SmartPointer();
		}
		gameObject.m_BypassDelete = true;
	}

	void Flock::Update(float i_DeltaTime)
	{
		if (!gameObject.HavePtr()) {
			return;
		}

		// Get a list of neighbors (other objects
		neighbors.clear();
		for (int i = 0; i < FlockingList.size(); i++)
		{
			if (FlockingList[i] != gameObject && (FlockingList[i]->Position() - gameObject->Position()).GetLengthSqr() < neighborDistanceSqr)
			{
				neighbors.push_back(FlockingList[i]);
			}
		}
		if (neighbors.size() == 0)
		{
			// No neighbors so nothing to create a flocking pattern
			return;
		}

		Math::cVector steering;

		//Create our separation Vector
		Math::cVector separation;
		{
			Math::cVector distanceVec;
			for (int i = 0; i < neighbors.size(); i++)
			{
				distanceVec = gameObject->Position() - neighbors[i]->Position();
				if (distanceVec.GetLengthSqr() != 0)
				{
					separation += distanceVec.CreateNormalized() / distanceVec.GetLength();
				}
			}
		}

		// Create our Alignment Vector
		Math::cVector alignment;
		{
			Math::cVector velocitySum;
			for (int i = 0; i < neighbors.size(); i++)
			{
				velocitySum += neighbors[i]->Rigidbody()->Velocity();
			}
			if (velocitySum.GetLengthSqr() > Math::s_epsilon) {
				alignment = (velocitySum / neighbors.size()).CreateNormalized();
			}
		}

		// Create our Cohesion Vector
		Math::cVector cohesion;
		{
			Math::cVector positionAvg;
			for (int i = 0; i < neighbors.size(); i++)
			{
				positionAvg += neighbors[i]->Position();
			}
			positionAvg = positionAvg / neighbors.size();
			if (positionAvg == gameObject->Position())
			{
				cohesion = Math::cVector(0);
			}
			else 
			{
				cohesion = (positionAvg - gameObject->Position()).CreateNormalized();
			}
		}

		// Add our 3 vectors with the appropriate weights
		steering = (separation * separationWeight) + (alignment * alignmentWeight) + (cohesion * cohesionWeight);
		steering.Normalize();
		
		m_Rigidbody->AddVelocity(steering);
		if (m_Rigidbody->Velocity().GetLengthSqr() > MaxSpeedSqr())
		{
			m_Rigidbody->Velocity(m_Rigidbody->Velocity().CreateNormalized() * MaxSpeed());
		}
	}
}