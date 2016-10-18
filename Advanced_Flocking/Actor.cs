/*
    Author: Ryan Kirschman
	Date: 9/17/2016

    This script is a movement handler for a simple actor.
    It does not use the physics engine, instead simulating the physics itself.

    It takes in a steering input each frame for movement.
 */

using UnityEngine;
using System.Collections;

public class Actor : MonoBehaviour {

    public bool FaceDirection;

    public Vector3 Velocity;

    [SerializeField]
    protected float _MaxSpeed;
    public float MaxSpeed
    {
        get { return _MaxSpeed; }
        set
        {
            //_MaxSpeedSqr = value * value;
            _MaxSpeed = value;
        }
    }
    //protected float _MaxSpeedSqr;

    [SerializeField]
    public float SteeringAccel;

    protected Vector3 _Acceleration, _Steering;

    public void Steer(float x, float y, float z)
    {
        Steer(new Vector3(x, y, z));
    }
    public void Steer(Vector3 input)
    {
        _Steering = Vector3.ClampMagnitude(input, 1.0f);
        _Acceleration = _Steering * SteeringAccel;
    }

	void Start () {
        MaxSpeed = MaxSpeed;
	}

    void Update()
    {
        if(Input.GetKey(KeyCode.LeftArrow))
        {
            Steer(Vector3.left);
        }
        else if(Input.GetKey(KeyCode.RightArrow))
        {
            Steer(Vector3.right);
        }

        if (Input.GetKey(KeyCode.UpArrow))
        {
            Steer(Vector3.forward);
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            Steer(Vector3.back);
        }
    }
	
	void FixedUpdate ()
    {
        Velocity += _Acceleration * Time.deltaTime;
        Velocity = Vector3.ClampMagnitude(Velocity, _MaxSpeed);
        transform.position += (Velocity * Time.deltaTime);
        if (FaceDirection)
        {
            transform.rotation = Quaternion.LookRotation(Vector3.back, Vector3.Normalize(Velocity));
        }

        _Steering = Vector3.zero;
        _Acceleration = Vector3.zero;
    }
}
