/*
    Author: Ryan Kirschman
	Date: 5/25/2016

    This class controls the 4D elements and transformations of a 4D Object.
    
    Much like a Transform, it can have a parent or children.
    It stores a local coordinate (the W coordinate of a 4D position vector).
    The global coordinate is affected by the parent's coordinate if there is one.

    As this class controls the transformations, it maintains a list of ITransformations,
    an interface class that controls one specific transformation.
    These transformations can range from position or scale transformations to color modification of a material
    or even controlling an animation or blending one mesh into another.
 */

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Hyper
{
    [ExecuteInEditMode]
    public class Transformation_Handler : MonoBehaviour
    {
        [SerializeField]
        private bool _isActive = true;
        public bool IsActive
        {
            get
            {
                if (!_isActive)
                {
                    return false;
                }
                if (_ParentHandler != null)
                {
                    return _ParentHandler.IsActive;
                }
                return _isActive;
            }
            set
            {
                _isActive = value;
                if (value)
                {
                    Activate();
                }
                else
                {
                    Deactivate();
                }
            }
        }

        [SerializeField]
        private float _Current4DLocation;
        public float Current4DLocation
        {
            get
            {
                if (_ParentHandler != null)
                {
                    return _Current4DLocation + _ParentHandler.Current4DLocation;
                }
                return _Current4DLocation;
            }
            set
            {

                _Current4DLocation = value;
                if (_IsShadowObject)
                {
                    return;
                }
                _AnalogObject.Current4DLocation = value;
            }
        }

        [SerializeField]
        private bool _IsShadowObject;
        public bool IsShadowObject
        {
            get { return _IsShadowObject; }
            set { _IsShadowObject = value; }
        }

        [SerializeField]
        private Transformation_Handler _AnalogObject;
        public Transformation_Handler AnalogObject
        {
            get { return _AnalogObject; }
        }

        [SerializeField]
        private Transformation_Handler _ParentHandler;
        public Transformation_Handler ParentHandler
        {
            get { return _ParentHandler; }
            set { _ParentHandler = value; }
        }

        [SerializeField]
        private List<Transformation_Handler> _ChildHandlers = new List<Transformation_Handler>();
        public List<Transformation_Handler> ChildHandlers
        {
            get { return _ChildHandlers; }
        }

        [SerializeField]
        private List<ITransformation> _Transformations = new List<ITransformation>();
        public List<ITransformation> Transformations
        {
            get { return _Transformations; }
        }

        private float localized4D_Coord;

        public void Update()
        {
            localized4D_Coord = Global_Variables.Player4D_Location - Current4DLocation;

            if (_IsShadowObject)
            {
                localized4D_Coord += Global_Variables.HyperVisor_Location;
            }

            for (int i = 0; i < _Transformations.Count; i++)
            {
                if (_Transformations[i] != null && _Transformations[i].enabled)
                {
                    _Transformations[i].OnUpdate(localized4D_Coord);
                }
            }
        }
    }
}