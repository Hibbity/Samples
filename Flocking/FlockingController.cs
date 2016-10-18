/*
    Author: Ryan Kirschman
	Date: 9/9/2015

    This is an AI behavior used to simulate flocking. It uses the UnityEngine.
    The IActor it communicates handles all movement, much like a rigidbody.
    This class handles the AI for the movement.
    This currently works for 2D. To work in 3D, the Vector2 instances should be Vector3,
    and the IActor would need to take a Vector3 for input.
 */

using UnityEngine;
using System.Collections.Generic;

[RequireComponent(typeof (IActor))]
public class FlockingController : MonoBehaviour {
	static List<IActor> _actorList;

    public float neighborDistance = 5.0f;
    public float separationWeight = 5.0f;
	public float alignmentWeight = 1.241379f;
	public float cohesionWeight = 3.534483f;

    private IActor _actor;

    private void Start() {
        _actor = GetComponent<IActor>();
    }

    private void Update() {
		// Keep a list of actors who are within the neighborDistance
		if (_actorList == null) {
			GameObject[] gameObjects = FindObjectsOfType<GameObject>();
			_actorList = new List<IActor>();
			foreach(GameObject gObject in gameObjects){
				IActor t_Actor = gObject.GetComponent<IActor>();
				if(t_Actor != null && t_Actor != this){
					_actorList.Add(t_Actor);
				}
			}
		}
		List<IActor> neighbors = new List<IActor> ();

		for (int i = 0; i < _actorList.Count; i++) {
			if((_actorList[i].Position - transform.position).sqrMagnitude < neighborDistance * neighborDistance){
				neighbors.Add(_actorList[i]);
			}
		}

        Vector2 steering = Vector2.zero;  // FIXME

		// Separation
		Vector2 separationVector = Vector2.zero;
		{
			Vector2 t_SepVec = Vector2.zero;
			foreach (IActor actor in neighbors) {
				Vector3 distanceVec = -actor.Position + transform.position;
				if(distanceVec.sqrMagnitude != 0){
					Vector3 invertedDistance = distanceVec.normalized / distanceVec.magnitude; 
					t_SepVec += new Vector2(invertedDistance.x, invertedDistance.y);
				}
			}
			//Debug.Log (name + ": " + t_SepVec.ToString("F4"));
			separationVector = t_SepVec;
		}

		// Aligment
		Vector2 alignmentVector = Vector2.zero;
		{
			Vector2 velocitySum = Vector3.zero;
			foreach (IActor actor in neighbors) {
				velocitySum += actor.Velocity;
			}
			alignmentVector = (velocitySum / neighbors.Count).normalized;
		}

		// Cohesion
		Vector2 cohesionVector = Vector2.zero;
		{
			Vector3 positionSum = Vector3.zero;
			foreach (IActor actor in neighbors) {
				positionSum += actor.Position;
			}
			Vector3 averagePos = positionSum / neighbors.Count;
			Vector3 t_Vector = (averagePos - transform.position).normalized;
			cohesionVector = new Vector2(t_Vector.x, t_Vector.y);
		}

		// Sum them up
		steering =  (separationVector * separationWeight) + 
					(alignmentVector * alignmentWeight) +
					(cohesionVector * cohesionWeight);

        // Pass all parameters to the character control script.
        _actor.SetInput( steering.x, steering.y );
    }
}