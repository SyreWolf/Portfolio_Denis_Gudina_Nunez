using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class MassSpring : MonoBehaviour {
    //Indicador de set de animaciones de viento
    public int set = 0;
    //Lista en que se guardarán los nodos
    public List<Node> listaNodos;
    //Lista en que se guardarán los muelles
    public List<Spring> listaSprings;
    //Lista en que se guardarán las conexiones de los triángulos de la malla
    public List<Edge> listaEdges;
    //Vector de gravedad
    public Vector3 g = new Vector3(0,9.8f,0);
    //Masa de los nodos
    public float mass = 100;
    //Constante elástica de los muelles
    public float k = 500;
    //Factor de tiempo
    public float h = 0.008f;
    //Vectores que aplican la fuerza del viento a la bandera
    Vector3 windbandera = new Vector3(0, 0, 0);
    Vector3 wind1 = new Vector3(10, 8, 8);
    Vector3 wind2 = new Vector3(5, 5, -4);
    Vector3 wind3 = new Vector3(8, 12, 13);
    Vector3 wind4 = new Vector3(4, 7, -1);
    //Vectores que aplican la fuerza del viento a los banners
    Vector3 windpropaganda = new Vector3(0, 0, 0);
    Vector3 wind5 = new Vector3(2, 0, 1);
    Vector3 wind6 = new Vector3(0, 0, 0);
    Vector3 wind7 = new Vector3(3, 0, 3);
    Vector3 wind8 = new Vector3(0, 0, 0);
    int contador = 0;
    //Métodos de integración
    public enum Integration
    {
        ExplicitEuler = 0,
        SymplecticEuler = 1,
    }
    public Integration integrationMethod;

	void Start () {
        //Se crean todas las listas que van a ser usadas para crear las conexiones de la malla
        //Vertices
        listaNodos = new List<Node>();
        //Muelles
        listaSprings = new List<Spring>();
        //Conexiones que usarán los muelles más adelante
        listaEdges = new List<Edge>();
        /*Se usan las siguientes instrucciones para crear un objeto de la malla dada
        y se obtienen dos arrays, uno con los vértices y otro con los triángulos y su orden*/
        Mesh mesh = this.GetComponent<MeshFilter>().mesh;
        Vector3[] vertices = mesh.vertices;     
        int[] triangles = mesh.triangles;

        foreach (Vector3 vertice in vertices)
        {
            /*Se añade un CheckSphere para que detecte la colisión con los fixer que tengan
            el tag 9, y así hacer que los nodos en contacto con esos objetos sean fijos*/
            if (Physics.CheckSphere(transform.TransformPoint(vertice), 0.1f, 1<<9))
            {
                Node vertex = new Node();
                //Se asigna la posición, que es la transformada del vertice
                vertex.pos = transform.TransformPoint(vertice);
                //Se asigna la masa, que es la masa total de los vértices por la longitud del vector de vértices
                vertex.mass = mass / vertices.Length;
                //Se indica que el nodo es fijo
                vertex.fixedNode = true;
                //Se añade el vértice a la lista de nodos
                listaNodos.Add(vertex);
            }
            //En caso de que no colisionen con uno de esos fixer se crean como vértices no fijos
            else
            {
                Node vertex = new Node();
                //Se asigna la posición, que es la transformada del vertice
                vertex.pos = transform.TransformPoint(vertice);
                //Se asigna la masa, que es la masa total de los vértices por la longitud del vector de vértices
                vertex.mass = mass / vertices.Length;
                //Se indica que el nodo no es fijo
                vertex.fixedNode = false;
                //Se añade el vértice a la lista de nodos
                listaNodos.Add(vertex);
            }
            
        }

        //Se recorren los triángulos de la lista de triángulos
        for(int i = 0; i< triangles.Length; i+=3)
        {
            /*Si el ID del triángulo posterior es mayor que el del actual se ordenan
            de manera ClockWise u horaria*/
            if (triangles[i] < triangles[i + 1])
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i], triangles[i + 1], triangles[i + 2]));
            }
            /*Si el ID del triángulo posterior es menor que el del actual se ordenan
            de manera CounterClockWise u antihoraria*/
            else
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i], triangles[i + 2], triangles[i + 1]));
            }
            /*Si el ID del triángulo posterior es mayor que el del actual se ordenan
            de manera ClockWise u horaria*/
            if (triangles[i + 1] < triangles[i + 2])
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i + 1], triangles[i + 2], triangles[i]));
            }
            /*Si el ID del triángulo posterior es menor que el del actual se ordenan
            de manera CounterClockWise u antihoraria*/
            else
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i + 1], triangles[i], triangles[i + 2]));
            }
            /*Si el ID del triángulo posterior es mayor que el del actual se ordenan
            de manera ClockWise u horaria*/
            if (triangles[i + 2] < triangles[i])
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i + 2], triangles[i], triangles[i + 1]));
            }
            /*Si el ID del triángulo posterior es menor que el del actual se ordenan
            de manera CounterClockWise u antihoraria*/
            else
            {
                /*Se añade un Edge que contiene los ID de los vértices que están conectados
                en ese triángulo y en que orden lo están*/
                listaEdges.Add(new Edge(triangles[i + 2], triangles[i + 1], triangles[i]));
            }
        }


        /*Se recorren todos los Edges para crear los diferentes muelles que conectarán los vértices,
         de acuerdo a las indicaciones de los Edges guardados previamente*/
        Edge last = null;
        foreach(Edge e in listaEdges)
        {
            //Se pone esta condición para evitar el primer caso, en que el Edge last está vacío
            if(e != last)
            {
                /*Se crea un muelle y se conectan los vertex A y B del Edge en cuestión
                con los extremos del muelle que está siendo creado*/
                Spring muelle = new Spring();
                //Se asigna el nodo A
                muelle.nodeA = listaNodos[e.vertexA];
                //Se asigna el nodo B 
                muelle.nodeB = listaNodos[e.vertexB];
                //Se asigna el valor de constante elástica del muelle
                muelle.k = k;

                //Se añade el muelle a la lista de muelles
                listaSprings.Add(muelle);
                //print(0 + " " + muelle.nodeA.pos + " " + muelle.nodeB.pos);

            }
            //Se asigna que last es ahora igual al Edge que acabamos de iterar
            last = e;
        }

        /*Ordenamos toda la lista de Edges de acuerdo al valor del vertex A y después de acuerdo al valor del
        vertex B de cada Edge, de manera que podamos encontrar los casos en que son iguales y poder crear los
        muelles restantes que conectarían los vertexOther de los Edges*/
        listaEdges = listaEdges.OrderBy(list => list.vertexA).OrderBy(list => list.vertexB).ToList();

        last = null;
        foreach (Edge e in listaEdges)
        {
            //Se pone esta condición para evitar el primer caso, en que el Edge last está vacío
            if (last != null)
            {
                //Si el valor de vertex A y vertex B es el mismo en dos Edges...
                if (e.vertexA == last.vertexA && e.vertexB == last.vertexB)
                {
                    /*Se crea un muelle y se conectan los vertexOther de los Edges en cuestión
                    con los extremos del muelle que está siendo creado*/
                    Spring muelle = new Spring();
                    //Se asigna el nodo A
                    muelle.nodeA = listaNodos[last.vertexOther];
                    //Se asigna el nodo B 
                    muelle.nodeB = listaNodos[e.vertexOther];
                    //Se asigna el valor de constante elástica del muelle
                    muelle.k = k;

                    listaSprings.Add(muelle);
                    //print(0 + " " + muelle.nodeA.pos + " " + muelle.nodeB.pos);
                }

                //Si el valor de vertex A y entre vertex B solo hay una unidad de distancia...
                if (e.vertexA == last.vertexA && Math.Abs(e.vertexB-last.vertexB)==1)
                {
                    /*Se crea un muelle y se conectan los vertexOther de los Edges en cuestión
                    con los extremos del muelle que está siendo creado*/
                    Spring muelle = new Spring();
                    //Se asigna el nodo A
                    muelle.nodeA = listaNodos[last.vertexOther];
                    //Se asigna el nodo B
                    muelle.nodeB = listaNodos[e.vertexOther];
                    //Se asigna el valor de constante elástica del muelle
                    muelle.k = k;

                    //Se añade el muelle a la lista de muelles
                    listaSprings.Add(muelle);
                    //print(0 + " " + muelle.nodeA.pos + " " + muelle.nodeB.pos);
                }
            }
            //Se asigna que last es ahora igual al Edge que acabamos de iterar
            last = e;
        }

        foreach (Spring spring in listaSprings)
        {
            spring.dir = spring.nodeA.pos - spring.nodeB.pos;
            spring.length0 = spring.dir.magnitude;
            spring.length = spring.length0;
            spring.dir = Vector3.Normalize(spring.dir);
            spring.pos = (spring.nodeA.pos + spring.nodeB.pos) / 2;
            spring.rotation = Quaternion.FromToRotation(Vector3.up, spring.dir);
        }
    }
	
	// Update is called once per frame
	void Update () {
        Mesh mesh = this.GetComponent<MeshFilter>().mesh;
        List<Vector3> newpos = new List<Vector3>();
        randomize();
        contador++;
        /*print(contador);
        print(wind);*/
        //Actualizamos las posiciones de los nodods de la malla para simular el movimiento
        foreach(Node node in listaNodos)
        {
            //Se actualiza la posición de los nodos a la transformada de la posición
            newpos.Add(transform.InverseTransformPoint(node.pos));
        }
        //Se añade la nueva posición a los vértices
        mesh.SetVertices(newpos);
	}

    private void FixedUpdate()
    {
            switch (integrationMethod)
            {
                case Integration.ExplicitEuler:
                    integrateExplicitEuler();
                    break;
                case Integration.SymplecticEuler:
                    integrateSymplecticEuler();
                    break;
                default:
                    print("ERROR METODO DESCONOCIDO");
                    break;
            }

            foreach(Spring spring in listaSprings)
            {
                spring.length = (spring.nodeA.pos - spring.nodeB.pos).magnitude;
                spring.pos = (spring.nodeA.pos + spring.nodeB.pos) / 2;
                spring.dir = spring.nodeA.pos - spring.nodeB.pos;
                spring.dir = Vector3.Normalize(spring.dir);
                spring.rotation = Quaternion.FromToRotation(Vector3.up, spring.dir);
            }
    }

    void integrateExplicitEuler()
    {
        if (set == 0)
        {
            foreach (Node nodo in listaNodos)
            {
                //Ahora sumamos a la fuerza el vector del viento que hemos designado al principio
                nodo.force = -nodo.mass * g + windbandera;
            }
        }
        else
        {
            foreach (Node nodo in listaNodos)
            {
                //Ahora sumamos a la fuerza el vector del viento que hemos designado al principio
                nodo.force = -nodo.mass * g + windpropaganda;
            }
        }
        foreach (Spring spring in listaSprings)
        {
            Vector3 f;
            f = spring.k *
                (spring.length - spring.length0) *
                spring.dir;
            spring.nodeB.force += f;
            spring.nodeA.force -= f;
        }

        foreach (Node nodo in listaNodos)
        {
            if (!nodo.fixedNode)
            {
                nodo.pos += h * nodo.vel;
                nodo.vel += nodo.force * h / nodo.mass;   
            }
        }
    }

    void integrateSymplecticEuler()
    {
        if (set == 0)
        {
            foreach (Node nodo in listaNodos)
            {
                //Ahora sumamos a la fuerza el vector del viento que hemos designado al principio
                nodo.force = -nodo.mass * g + windbandera;
            }
        }
        else
        {
            foreach (Node nodo in listaNodos)
            {
                //Ahora sumamos a la fuerza el vector del viento que hemos designado al principio
                nodo.force = -nodo.mass * g + windpropaganda;
            }
        }
        
        foreach (Spring spring in listaSprings)
        {
            Vector3 f;
            f = spring.k *
                (spring.length - spring.length0) *
                spring.dir;
            spring.nodeB.force += f;
            spring.nodeA.force -= f;
            applyDamping(spring);
        }

        foreach (Node nodo in listaNodos)
        {
            if (!nodo.fixedNode)
            {
                nodo.vel += nodo.force * h / nodo.mass;
                nodo.pos += h * nodo.vel;
            } 
        }
    }

    void applyDamping(Spring spring)
    {
        spring.nodeA.force += -spring.dAbsolute * spring.nodeA.vel;
        spring.nodeB.force += -spring.dAbsolute * spring.nodeB.vel;

        spring.nodeA.force += -spring.dRotation * (spring.nodeA.vel - spring.nodeB.vel);
        spring.nodeB.force += -spring.dRotation * (spring.nodeB.vel - spring.nodeA.vel);

        spring.nodeA.force += -spring.dDeformation * Vector3.Dot(spring.nodeA.vel - spring.nodeB.vel, spring.dir) * spring.dir;
        spring.nodeB.force += -spring.dDeformation * Vector3.Dot(spring.nodeB.vel - spring.nodeA.vel, spring.dir) * spring.dir;
    }

    //Prototipo de fuerzas de penalty (No funcional)
    /*Vector3 penalty(Node n)
    {
        Vector3 fpen;
        Vector3 mpos = new Vector3(15, 20, 0);
        fpen = k2 * Vector3.Cross(n.pos - mpos, Vector3.Cross(n.pos, n.vel));
        return fpen;
    }*/

    //Aquí lo que hacemos es pintar tanto los muelles como los nodos para poder hacer comprobaciones desde la pantalla de Unity
    void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.yellow;
        foreach(Node node in listaNodos)
        {
            Gizmos.DrawSphere(node.pos, 0.1f);

        }

        Gizmos.color = Color.blue;
        foreach (Spring spring in listaSprings)
        {
            Gizmos.DrawLine(spring.nodeA.pos, spring.nodeB.pos);

        }
    }

    //Va cambiando la bandera de acuerdo a los ciclos de frames
    void randomize()
    {
        if(set == 0)
        {
            if (contador <= 100)
            {
                windbandera = wind1;
            }
            else if (contador <= 200 && contador > 100)
            {
                windbandera = wind2;
            }
            else if (contador <= 300 && contador > 200)
            {
                windbandera = wind3;
            }
            else if (contador < 400 && contador > 300)
            {
                windbandera = wind4;
            }
            else if (contador >= 400)
            {
                contador = 0;
            }
        }
        else if (set == 1)
        {
            if (contador <= 100)
            {
                windpropaganda = wind5;
            }
            else if (contador <= 200 && contador > 100)
            {
                windpropaganda = wind6;
            }
            else if (contador <= 300 && contador > 200)
            {
                windpropaganda = wind7;
            }
            else if (contador < 400 && contador > 300)
            {
                windpropaganda = wind8;
            }
            else if (contador >= 400)
            {
                contador = 0;
            }
        }
      
    }
}