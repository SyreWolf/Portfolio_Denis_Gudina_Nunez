using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Se crea la clase Edge para almacenar los triángulos que harán las interacciones entre sus vértices
public class Edge {

    public int vertexA;
    public int vertexB;
    public int vertexOther;

    public Edge(int vertexA, int vertexB, int vertexOther)
    {
        this.vertexA = vertexA;
        this.vertexB = vertexB;
        this.vertexOther = vertexOther;
    }
}
