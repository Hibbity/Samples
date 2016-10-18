/*
    Author: Ryan Kirschman
	Date: 8/3/2016
    Description: A generic timer class. It keeps track of how much time is remaining
*/

using UnityEngine;

[System.Serializable]
public class Timer
{
    public float TimeScale = 1; // Used when calling Update. Scales UnityEngine.Time.deltaTime.

    private float _cTime; // Time since starting the timer.
    private float _GoalTime; // The goal for this timer. Used to know when the timer is complete
    private bool _Complete;
    private float _PercentDone; // A percentage of how much time has passed in relation to the goal

    public float CurrentTime
    {
        get { return _cTime; }
    }
    public float GoalTime
    {
        get { return _GoalTime; }
    }
    public bool Complete
    {
        get { return _Complete; }
    }
    public float PercentDone
    {
        get { return _PercentDone; }
    }

    public float TimeRemaining
    {
        get { return _GoalTime - _cTime; }
    }

    public Timer()
    {
        _GoalTime = 0;
    }
    public Timer(float GoalTime)
    {
        _GoalTime = GoalTime;
    }

    /// <summary>
    /// Reset the timer to 0 with the current goal time remaining the same
    /// </summary>
    public void Reset()
    {
        _cTime = 0;
        _Complete = false;
    }

    /// <summary>
    /// Reset the timer to 0 with a new goal time
    /// </summary>
    /// <param name="Goal">The new goal for the timer</param>
    public void Reset(float Goal)
    {
        _GoalTime = Mathf.Max(Goal, Time.deltaTime);
        _cTime = 0;
        _Complete = false;
    }

    /// <summary>
    /// Sets the current time for the timer
    /// </summary>
    /// <param name="cTime"></param>
    public void Set(float cTime)
    {
        _cTime = cTime;
        if (_cTime > _GoalTime)
        {
            _Complete = true;
        }
    }

    /// <summary>
    /// Updates the timer using Unity's Time.deltaTime as well as the timer's TimeScale
    /// </summary>
    public void Update()
    {
        UnscaledUpdate(Time.deltaTime * TimeScale);
    }

    /// <summary>
    /// Updates the timer using Unity's fixed time scale. It does not use the timer's TimeScale.
    /// </summary>
    public void FixedUpdate()
    {
        UnscaledUpdate(Time.fixedDeltaTime);
    }

    /// <summary>
    /// Updates the timer with the amount provided. It does not use the timer's TimeScale.
    /// </summary>
    /// <param name="amount">How much the time the timer should be updated with</param>
    public void UnscaledUpdate(float amount)
    {
        _cTime += amount;

        _PercentDone = _cTime / _GoalTime;

        if (_cTime > _GoalTime)
        {
            _Complete = true;
        }
    }
}
