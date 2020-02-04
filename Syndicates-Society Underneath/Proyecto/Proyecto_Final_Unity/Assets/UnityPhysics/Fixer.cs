using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Se crea un objeto Fixer que hará de sujeción a ciertos nodos
public class Fixer : MonoBehaviour {

    public Renderer render;
	// Use this for initialization
	void Start () {
        //Se desactiva el renderizado de este objeto en la escena
        render = GetComponent<Renderer>();
        render.enabled = false;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
