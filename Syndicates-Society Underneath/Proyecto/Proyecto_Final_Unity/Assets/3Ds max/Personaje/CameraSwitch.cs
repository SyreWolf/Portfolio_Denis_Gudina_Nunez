using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSwitch : MonoBehaviour
{

    public GameObject cOne;
    public GameObject cTwo;
    public GameObject cThree;
    public GameObject cFour;

    // Use this for initialization
    void Start()
    {
        //Se escoge como cámara incial la guardada en memoria
        cameraPos(PlayerPrefs.GetInt("CameraPosition"));
    }

    // Update is called once per frame
    void Update()
    {
        //Se hace el cambio de cámara con teclado
        switchCamera();
    }

    //Si se detecta la tecla se cambia de cámara
    void switchCamera()
    {
        if (Input.GetKeyDown(KeyCode.C))
        {
            contador();
        }
    }

    //Contador de cámara
    void contador()
    {
        int cameracontador = PlayerPrefs.GetInt("CameraPosition");
        cameracontador++;
        cameraPos(cameracontador);
    }

    //Retorno de cámara
    void cameraPos(int camPos)
    {
        if (camPos > 3)
        {
            camPos = 0;
        }

        //Se cambia la cámara guardada en memoria
        PlayerPrefs.SetInt("CameraPosition", camPos);

        //Se escoge la cámara 1
        if (camPos == 0)
        {
            cOne.SetActive(true);
            cTwo.SetActive(false);
            cThree.SetActive(false);
            cFour.SetActive(false);
        }

        //Se escoge la cámara 2
        if (camPos == 1)
        {
            cOne.SetActive(false);
            cTwo.SetActive(true);
            cThree.SetActive(false);
            cFour.SetActive(false);
        }

        //Se escoge la cámara 3
        if (camPos == 2)
        {
            cOne.SetActive(false);
            cTwo.SetActive(false);
            cThree.SetActive(true);
            cFour.SetActive(false);
        }

        //Se escoge la cámara 4
        if (camPos == 3)
        {
            cOne.SetActive(false);
            cTwo.SetActive(false);
            cThree.SetActive(false);
            cFour.SetActive(true);
        }

    }
}