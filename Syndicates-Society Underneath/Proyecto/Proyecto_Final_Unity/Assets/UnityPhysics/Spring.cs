using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Se quita el MonoBehaviour para añadirlo directamente en el script MassSpring
public class Spring {

    public Vector3 pos;
    public Vector3 dir;
    public Quaternion rotation;
    public float k = 100f;
    public float length0;
    public float length;
    public Node nodeA;
    public Node nodeB;
    public float defaultSize = 2f;
    public float dAbsolute = 0.1f;
    public float dRotation = 1f;
    public float dDeformation = 10f;

    public Spring()
    {

    }
	// Use this for initialization
	/*void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        /*transform.position = pos;
        transform.localScale = new Vector3(transform.localScale.x, (length / defaultSize), transform.localScale.z);
        transform.rotation = rotation;
    }*/
}
