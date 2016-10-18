/*
    Author: Ryan Kirschman
	Date: 9/17/2016

    This is a manager for a group of AI_Flocking objects.
    
    It will maintain a List of AI_Flcoking objects, as well as a List of Transforms for control points.
    It will also maintain the different weights being used.
 */

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Flocking_Manager : MonoBehaviour
{
    public List<AI_Flocking> Flockers;

    public List<Transform> ControlPoints;
    
    public float SeparationWeight;
    public float AlignmentWeight;
    public float CohesionWeight;
    public float RandomWeight;
    public float ControlWeight;

    private bool _Initialized;

    public float TimeDifferenceForInitialization;
    private int FlockerNumber;

    [ContextMenu("Build Flockers")]
    public void BuildFlockers()
    {
        Flockers = new List<AI_Flocking>(GetComponentsInChildren<AI_Flocking>());
    }

    public virtual bool Initialize()
    {
        if(_Initialized)
        {
            return true;
        }

        _Initialized = true;

        FlockerNumber = Flockers.Count - 1;

        if (TimeDifferenceForInitialization == 0)
        {
            while (FlockerNumber >= 0)
            {
                InitializeFlocker();
            }
        }
        else
        {
            StartCoroutine(InitializeFlockerOverTime());
        }

        return false;
    }

    private IEnumerator InitializeFlockerOverTime()
    {
        while (FlockerNumber >= 0)
        {
            InitializeFlocker();
            yield return new WaitForSeconds(TimeDifferenceForInitialization);
        }
    }

    /// <summary>
    /// Initializes an AI_Flocking object
    /// </summary>
    private void InitializeFlocker()
    {
        Flockers[FlockerNumber].OnInit();
        Flockers[FlockerNumber]._Manager = this;
        StartCoroutine(FoldMeshes(Flockers[FlockerNumber].GetComponent<Blend_Mesh>()));
        FlockerNumber--;
    }

    // The Blend_Mesh script blends one mesh with x vertices into another mesh with x vertices.
    /// <summary>
    /// Blends one sheet into another sheet.
    /// </summary>
    /// <param name="blender"></param>
    /// <returns></returns>
    private IEnumerator FoldMeshes(Blend_Mesh blender)
    {
        yield return new WaitForSeconds(0.25f);

        blender.StartCoroutine(blender.BlendMesh());
    }

    void Start()
    {
        Initialize();
    }

    void Update()
    {

    }

}
