/*
    Author: Ryan Kirschman
	Date: 8/3/2016
    Description: The base class for a ranged weapon. This derives from the Weapon_Base class.
                This class should be derived from for any ranged weapon that needs special functionality.
*/

using UnityEngine;
using System.Collections;

public class Ranged_Weapon_Base : Weapon_Base {

    [SerializeField]
    protected GameObject _BulletPrefab; // Which Bullet should the weapon use?

    [SerializeField]
    protected Transform _firingPoint; // Where do the bullets fire from?

    protected Buffer<Bullet_Base> _bulletBuffer; // A buffer to contain bullets. This is used to cutdown on garbage collection.
    public Buffer<Bullet_Base> BulletBuffer
    {
        get { return _bulletBuffer; }
    }
    
    [SerializeField]
    protected int _BufferSize; //How many bullets should the buffer hold?

    public float _RateOfFire = 0.2f; // How often can a bullet be fired.
    protected Timer _tm_Fire; // The timer used to ensure 1 bullet is fired during every cycle of length _RateOfFire

    protected Bullet_Base _BulletFired; // Which bullet was most recently fired. Used to cutdown on garbage collection.

    public override bool Initialize()
    {
        if (!base.Initialize())
        {
            return false;
        }

        // Initialize the buffer and add bullets into the buffer
        _bulletBuffer = new Buffer<Bullet_Base>(null, null);
        GameObject bullet;
        for (int i = 0; i < _BufferSize; i++)
        {
            bullet = Instantiate<GameObject>(_BulletPrefab);
            bullet.transform.SetParent(transform);
            bullet.SetActive(false);
            bullet.GetComponent<Bullet_Base>().Initialize(this);
            _bulletBuffer.AddObject(bullet.GetComponent<Bullet_Base>());
        }

        _tm_Fire = new Timer();

        return true;
    }

    protected override void OnUpdate()
    {
        base.OnUpdate();
        if(!_tm_Fire.Complete)
        {
            _tm_Fire.Update();
        }
    }

    public override void Attack()
    {
        if (!_tm_Fire.Complete)
        {
            return;
        }

        _BulletFired = _bulletBuffer.GetFree() as Bullet_Base;
        if (_BulletFired != null)
        {
            _BulletFired.Activate(_firingPoint.position, _firingPoint.eulerAngles, _BaseDamage);
        }
        _tm_Fire.Reset(_RateOfFire);
    }
}
