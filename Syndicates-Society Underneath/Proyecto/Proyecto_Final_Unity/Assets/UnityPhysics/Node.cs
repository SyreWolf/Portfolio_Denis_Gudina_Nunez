using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Se quita el MonoBehaviour para añadirlo directamente en el script MassSpring
public class Node{

    public bool fixedNode;
    public float mass = 5f;
    public Vector3 pos;
    public Vector3 vel;
    public Vector3 force;

    public Node()
    {
        
    }
	// Use this for initialization
	/*public void Start () {
        //pos = transform.position;
	}
	
	// Update is called once per frame
	void Update () {
        transform.position = pos;
    }*/
}
