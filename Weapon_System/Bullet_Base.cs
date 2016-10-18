/*
    Author: Ryan Kirschman
	Date: 8/3/2016
    Description: The base class for a bullet.
                Bullets belong in their owner weapon's Bullet Buffer. 
                They are fired when they are activated. They are deactivated on collision with an object or when their timer runs out.

                The bullet damages an object by using Unity's Physics Collision system and then sending the collision info to Hyper.
                Hyper is a global namespace used for global functions and management.
*/

using UnityEngine;
using System.Collections;

[RequireComponent(typeof(Rigidbody))]
public class Bullet_Base : MonoBehaviour {

    protected bool _Initialized;
    protected bool _IsActive;

    protected Rigidbody _Rigidbody; // The rigidbody being used by the bullet as the bullet uses the Physics System.
    protected Ranged_Weapon_Base _Owner; // Which weapon "owns" the bullet

    [SerializeField]
    protected float _Speed = 25.0f; // How fast should the bullet be traveling
    [SerializeField]
    protected float _LifeTime = 10.0f; // How long does the bullet last before being deactivated and freed in the buffer.

    [SerializeField]
    protected float _Damage; //How much damage does this bullet do? Will be set by the weapon every time it is activated. 
    public float Damage
    {
        get { return _Damage; }
        set { _Damage = value; }
    }

    protected Timer _tm_Life; // The timer used to determine if the bullet should be deactivated due to time.

    // Initialize the bullet with its owner
    public bool Initialize(Ranged_Weapon_Base owner)
    {
        if (_Initialized)
        {
            return false;
        }

        _Initialized = true;

        _Rigidbody = GetComponent<Rigidbody>();
        _Owner = owner;

        _tm_Life = new Timer();
        return true;
    }

    void Update()
    {
        OnUpdate();
    }

    // While I currently only call OnUpdate, this method should future-proof the base-class and its child classes should I need to add more necessary functionality.
    /// <summary>
    /// The Update method that is called once per frame.
    /// </summary>
    protected virtual void OnUpdate()
    {
        if (_tm_Life != null)
        {
            _tm_Life.Update();
            if (_tm_Life.Complete)
            {
                Deactivate();
            }
        }
    }

    /// <summary>
    /// Activate the bullet and fire it
    /// </summary>
    /// <param name="position">The position from which the bullet is fired</param>
    /// <param name="angle">The angle at which bullet should be facing. It travels in a straight line.</param>
    /// <param name="damage">How much damage should the bullet do if it collides?</param>
    public virtual void Activate(Vector3 position, Vector3 angle, float damage)
    {
        if (_IsActive)
        {
            return;
        }
        _IsActive = true;
        gameObject.SetActive(true);
        transform.position = position;
        transform.eulerAngles = angle;

        _Rigidbody.velocity = transform.forward * _Speed;

        Damage = damage;

        _tm_Life.Reset(_LifeTime);
    }


    /// <summary>
    /// Deactivate the bullet. This will set the gameObject's active state to false and free it in its owner's bullet buffer.
    /// </summary>
    public virtual void Deactivate()
    {
        if (!_IsActive)
        {
            return;
        }
        _IsActive = false;
        _owner.BulletBuffer.FreeObject(this);

        gameObject.SetActive(false);

        _tm_Life.Reset(_LifeTime);
    }

    // If the bullet hits anything that it can collide with, deactivate it automatically. 
    protected void OnTriggerEnter(Collider col)
    {
        // Tell Hyper to damage the object belonging to the collider col.
        Hyper.DamageObject(col, _Damage);
        Deactivate();
    }
}
