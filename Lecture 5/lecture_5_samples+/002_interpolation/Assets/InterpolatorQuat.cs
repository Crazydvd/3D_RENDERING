using UnityEngine;
using System.Collections;

public class InterpolatorQuat : MonoBehaviour {

    public Vector3 startAngles;
    public Vector3 endAngles;

    [Range(0, 1)]
    public float current;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	}

    void OnValidate()
    {
        Quaternion start = Quaternion.Euler(startAngles);
        Quaternion end = Quaternion.Euler(endAngles);
        Quaternion result = Quaternion.Slerp(start, end, current);
        transform.rotation = result;
    }
}
