/*
    Author: Ryan Kirschman
	Date: 7/31/2016
    Description: A generic buffer to hold a certain amount of objects, 
                keeping track of which objects are in use and which aren't automatically.
                User can assign a delegate method for both activation and deactivation of objects
*/

using System.Collections.Generic;

[System.Serializable]
public class Buffer<T> {

    public delegate void VoidMethod(T ActOntThis);

    //The list of objects to  maintain
    private List<T> _Objects; 
    public List<T> MyObjects
    {
        get
        {
            return _Objects;
        }
    }

    // A list of corresponding booleans representing whether the object is in use or not.
    // A dictionary is not used so that I have more control over my objects and so they can be serialized if need be
    private List<bool> _ObjectBools;  
    public List<bool> ObjectBoolList
    {
        get { return _ObjectBools; }
    }

    public VoidMethod Activate;
    public VoidMethod Deactivate;

    #region Constructors
    public Buffer(VoidMethod i_ActivationMehod, VoidMethod i_DeactivationMethod)
    {
        _Objects = new List<T>();
        _ObjectBools = new List<bool>();
    }
    public Buffer(VoidMethod i_ActivationMehod, VoidMethod i_DeactivationMethod, int size)
    {
        _Objects = new List<T>(size);
        _ObjectBools = new List<bool>(size);
    }
    public Buffer(VoidMethod i_ActivationMehod, VoidMethod i_DeactivationMethod, List<T> copyObjects)
    {
        _Objects = copyObjects;
        _ObjectBools = new List<bool>(copyObjects.Count);
    }
    public Buffer(VoidMethod i_ActivationMehod, VoidMethod i_DeactivationMethod, T[] copyObjects)
    {
        _Objects = new List<T>();
        for(int i = 0; i < copyObjects.Length; i++)
        {
            _Objects.Add(copyObjects[i]);
        }
        _ObjectBools = new List<bool>(copyObjects.Length);
    }
    #endregion

    #region Accessors
    //will return the bool representing if a specific object is turned on or not
    public bool this[int i]
    {
        get
        {
            if (_ObjectBools.Count < i)
            {
                return false;
            }

            return _ObjectBools[i];
        }
        set
        {
            if (_ObjectBools.Count < i)
            {
                return;
            }

            _ObjectBools[i] = value;
        }
    }
    
    // Returns the next free object if one exists. Otherwise, it will throw an exception.
    public T GetFree()
    {
        for (int i = 0; i < _Objects.Count; i++)
        {
            if (!_ObjectBools[i])
            {
                if (Activate != null)
                {
                    Activate(_Objects[i]);
                }
                _ObjectBools[i] = true;
                return _Objects[i];
            }
        }

        throw new System.Exception("No free object in buffer");
    }

    #endregion

    #region Methods
    // Frees a specific object from the buffer
    public void FreeObject(T actOnThis)
    {
        if (Deactivate != null)
        {
            Deactivate(actOnThis);
        }
        for(int i = 0; i < _Objects.Count; i++)
        {
            if(_Objects[i].Equals(actOnThis))
            {
                _ObjectBools[i] = false;
                return;
            }
        }
    }

    //Adds a new object to the buffer. Defaults its active state to false.
    public void AddObject(T objectToAdd, bool isActive = false)
    {
        _Objects.Add(objectToAdd);
        _ObjectBools.Add(isActive);
    }

    #endregion
}
