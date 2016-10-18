/*
    Author: Ryan Kirschman
	Date: 9/17/2016

    This is an AI behavior used to simulate flocking. It uses the UnityEngine.
    
    Objects with this AI flock with other objects belonging to the Flocking_Manager.
    This is where it gets its various weights and control points.

    Unlike with normal flocking, this flocking allows for control points,
    which are points in space the flockers will flock around. It will choose its closest control point and use that.
    With multiple control points, separation can be strong enough to push other objects to other control points.
    As the control points move, the flockers will move with them. This allows for very dynamic group behavior.
 */

using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Actor))]
public class AI_Flocking : AI_Base
{
    [HideInInspector]
    public Flocking_Manager _Manager;

    public bool _Debug;

    protected Vector3 _Separation, _Alignment, _Cohesion, _Steering, _Control, _Random;

    protected Transform MyControlPoint;

    protected Actor _Actor;
    public Actor Actor
    {
        get { return _Actor; }
    }

    void Awake()
    {
        _Actor = GetComponent<Actor>();
    }

    public override bool OnInit()
    {
        if(base.OnInit())
        {
            return true;
        }

        
        return false;
    }

    public override bool OnUpdate()
    {
        if (!base.OnUpdate())
        {
            return false;
        }

        Separate();
        Align();
        Cohese();
        FocusControl();
        Calc_Random();

        _Steering = (_Separation * _Manager.SeparationWeight) +
                    (_Alignment * _Manager.AlignmentWeight) +
                    (_Cohesion * _Manager.CohesionWeight) +
                    (_Random * _Manager.RandomWeight) +
                    (_Control * _Manager.ControlWeight);

        _Actor.Steer(_Steering);
        return true;
    }

    public virtual void Separate()
    {
        Vector3 distanceVec;
        _Separation = Vector3.zero;
        foreach (AI_Flocking flock in _Manager.Flockers)
        {
            if(flock == this)
            {
                continue;
            }
            distanceVec = transform.position - flock.transform.position;
            if (distanceVec.sqrMagnitude != 0)
            {
                _Separation += distanceVec.normalized / distanceVec.sqrMagnitude;
            }
        }
    }

    public virtual void Align()
    {
        Vector3 velocitySum = Vector3.zero;
        foreach (AI_Flocking flock in _Manager.Flockers)
        {
            if (flock == this)
            {
                continue;
            }
            velocitySum += flock._Actor.Velocity;
        }
        _Alignment = (velocitySum / _Manager.Flockers.Count).normalized;
    }

    public virtual void Cohese()
    {
        Vector3 positionSum = Vector3.zero;
        foreach (AI_Flocking flock in _Manager.Flockers)
        {
            if (flock == this)
            {
                continue;
            }
            positionSum += flock.transform.position;
        }

        _Cohesion = ((positionSum / _Manager.Flockers.Count) - transform.position).normalized;
    }

    public virtual void FocusControl()
    {
        if(_Manager.ControlPoints.Count == 0)
        {
            if (_Debug)
            {
                Debug.Log("No Control Point");
            }
            _Control = Vector3.zero;
            return;
        }

        float MyControlPointDistSqr = Mathf.Infinity;
        foreach (Transform control in _Manager.ControlPoints)
        {
            if (_Debug)
            {
                Debug.Log(control.name + ": " + (transform.position - control.position).sqrMagnitude);
            }
            if ((transform.position - control.position).sqrMagnitude < MyControlPointDistSqr)
            {
                MyControlPointDistSqr = (transform.position - control.position).sqrMagnitude;
                MyControlPoint = control;
            }
        }

        _Control = (MyControlPoint.position - transform.position);
    }

    public void Calc_Random()
    {
        _Random = Random.onUnitSphere;
    }
}
