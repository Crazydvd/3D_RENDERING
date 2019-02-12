using UnityEngine;
using System.Collections;

public class InterpolatorEuler : MonoBehaviour {

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
        Vector3 result = Vector3.Lerp(startAngles, endAngles, current);
        transform.eulerAngles = result;
    }
}
