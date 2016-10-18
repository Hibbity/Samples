/*
    Author: Ryan Kirschman
	Date: 5/25/2016

    This class allows for a translational transformation.
    It matches a list of Vector3s with a list of 4D coordinates.
    It then interpolates between two Vector3s.

    Much like how an animation uses key frames to interpolate between,
    4D transformations use key coordinate-object pairs to interpolate between.
 */

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

namespace Hyper
{ 
    public class Position_Transformation : ITransformation
    {

        public List<Vector3> _Objects;

        public override void OnUpdate(float i_CurrentCoord)
        {
            int beginningIndex;
            float percentThrough;
            Transformation_State state = DetermineObjectsBetween(i_CurrentCoord, out beginningIndex, out percentThrough);
            if (state != Transformation_State.Middle)
            {
                transform.position = _Objects[beginningIndex];
                return;
            }

            transform.position = Vector3.Lerp(_Objects[beginningIndex],
                                                _Objects[beginningIndex + 1],
                                                percentThrough);
        }
    }
}
