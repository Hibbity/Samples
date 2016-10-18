/*
    Author: Ryan Kirschman
	Date: 8/3/2016
    Description: A base class for all weapons to derive from.
                The weapon has five methods to be overridden if needed:

                Initialize()
                OnUpdate()
                Attack()
                HoldAttack()
                ReleaseAttack()
*/

using UnityEngine;
using System.Collections;

public class Weapon_Base : MonoBehaviour {

    protected bool _Initialized; // Has the weapon been initialized?
    protected GameObject _Owner; // The Actor the weapon belongs to. Getter but no setter as a weapon should never be changing parents.
    public GameObject Owner
    {
        get { return _Owner; }
    }

    [SerializeField]
    protected float _BaseDamage; //How much base damage does this weapon do?
    public float BaseDamage
    {
        get { return _BaseDamage; }
        set { _BaseDamage = value; }
    }

    // The initialization method to be used externally by a global game manager or the Actor the weapon belongs to.
    public virtual bool Initialize(GameObject owner)
    {
        if (_Initialized)
        {
            return false;
        }

        _Initialized = true;
        _Owner = owner;

        return true;
    }
    
    void Start ()
    {

    }
    
    void Update () {
        OnUpdate();
	}

    // While I currently only call OnUpdate, this method should future-proof the base-class and its child classes should I need to add more necessary functionality.
    /// <summary>
    /// The Update method that is called once per frame.
    /// </summary>
    protected virtual void OnUpdate()
    {

    }

    /// <summary>
    /// Called at the start of an attack.
    /// </summary>
    public virtual void Attack()
    {
       
    }

    /// <summary>
    /// Called while an attack is being held.
    /// </summary>
    public virtual void HoldAttack()
    {

    }

    /// <summary>
    /// Called when an attack is released.
    /// </summary>
    public virtual void ReleaseAttack()
    {

    }
}
