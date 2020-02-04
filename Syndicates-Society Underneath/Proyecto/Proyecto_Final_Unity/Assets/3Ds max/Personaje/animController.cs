using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class animController : MonoBehaviour {

    float speedwalk = 2;
    float speedrun = 6;
    float rotSpeed = 80;
    float rot = 0f;
    float gravity = 9;

    Vector3 moveDir = Vector3.zero;
    public CharacterController characterController;
    public Animator characterAnimator;
    public AudioSource voice;
	// Use this for initialization
	void Start () {
        characterAnimator = GetComponent<Animator>();
        characterController = GetComponent<CharacterController>();
        voice.volume = 0.5f;
    }
	
	// Update is called once per frame
	void Update () {

        WalkAndRun();
        GetInput();
    }

    void WalkAndRun()
    {
        if (characterController.isGrounded)
        {
            if (Input.GetKey(KeyCode.W))
            {
                if (characterAnimator.GetBool("attacking") == true || characterAnimator.GetBool("taunting") == true || characterAnimator.GetBool("kicking") == true)
                {
                    return;
                }
                else if (Input.GetKey(KeyCode.LeftShift))
                {
                    characterAnimator.SetBool("walking", false);
                    characterAnimator.SetBool("running", true);
                    characterAnimator.SetInteger("condition", 4);
                    moveDir = new Vector3(0, 0, 1);
                    moveDir *= speedrun;
                    moveDir = transform.TransformDirection(moveDir);
                }
                else if (characterAnimator.GetBool("attacking") == false && characterAnimator.GetBool("taunting") == false && characterAnimator.GetBool("kicking") == false && characterAnimator.GetBool("running") == false)
                {
                    characterAnimator.SetBool("walking", true);
                    characterAnimator.SetInteger("condition", 1);
                    moveDir = new Vector3(0, 0, 1);
                    moveDir *= speedwalk;
                    moveDir = transform.TransformDirection(moveDir);
                }
            }

            if (Input.GetKeyUp(KeyCode.LeftShift) && Input.GetKey(KeyCode.W))
            {
                characterAnimator.SetBool("running", false);
                characterAnimator.SetBool("walking", true);
                characterAnimator.SetInteger("condition", 1);
                moveDir = new Vector3(0, 0, 0);
            }

            if (Input.GetKey(KeyCode.LeftShift) && Input.GetKeyUp(KeyCode.W))
            {
                characterAnimator.SetBool("running", false);
                characterAnimator.SetBool("walking", false);
                characterAnimator.SetInteger("condition", 0);
                moveDir = new Vector3(0, 0, 0);
            }

            if (Input.GetKeyUp(KeyCode.LeftShift) && !Input.GetKeyDown(KeyCode.W))
            {
                characterAnimator.SetBool("running", false);
                characterAnimator.SetBool("walking", false);
                characterAnimator.SetInteger("condition", 0);
                moveDir = new Vector3(0, 0, 0);
            }

            if (Input.GetKeyUp(KeyCode.W))
            {
                characterAnimator.SetBool("walking", false);
                if (characterAnimator.GetBool("attacking") == false && characterAnimator.GetBool("taunting") == false && characterAnimator.GetBool("kicking") == false)
                {
                    characterAnimator.SetInteger("condition", 0);
                }    
                moveDir = new Vector3(0, 0, 0);
            }
            if(characterAnimator.GetBool("running") == false)
            {
                if (Input.GetKey(KeyCode.S))
                {
                    if (characterAnimator.GetBool("attacking") == true || characterAnimator.GetBool("taunting") == true || characterAnimator.GetBool("kicking") == true)
                    {
                        return;
                    }
                    else if (characterAnimator.GetBool("attacking") == false && characterAnimator.GetBool("taunting") == false && characterAnimator.GetBool("kicking") == false && characterAnimator.GetBool("running") == false)
                    {
                        characterAnimator.SetBool("walking", true);
                        characterAnimator.SetInteger("condition", 1);
                        moveDir = new Vector3(0, 0, -1);
                        moveDir *= speedwalk;
                        moveDir = transform.TransformDirection(moveDir);
                    }
                }

                if (Input.GetKeyUp(KeyCode.S))
                {
                    characterAnimator.SetBool("walking", false);
                    if (characterAnimator.GetBool("attacking") == false && characterAnimator.GetBool("taunting") == false && characterAnimator.GetBool("kicking") == false && characterAnimator.GetBool("running") == false)
                    {
                        characterAnimator.SetInteger("condition", 0);
                    }
                    moveDir = new Vector3(0, 0, 0);
                }
            }
            
        }

        rot += Input.GetAxis("Horizontal") * rotSpeed * Time.deltaTime;
        transform.eulerAngles = new Vector3(0, rot, 0);

        moveDir.y -= gravity * Time.deltaTime;
        characterController.Move(moveDir * Time.deltaTime);
    }

    void GetInput()
    {
        if (characterController.isGrounded)
        {
            if (Input.GetMouseButtonDown(0))
            {
                if (characterAnimator.GetBool("walking") == true)
                {
                    characterAnimator.SetBool("walking", false);
                    characterAnimator.SetInteger("condition", 0);
                }else if (characterAnimator.GetBool("running") == true)
                {
                    characterAnimator.SetBool("running", false);
                    characterAnimator.SetInteger("condition", 0);
                }
                if (characterAnimator.GetBool("walking") == false && characterAnimator.GetBool("running") == false)
                {
                    Attacking();
                }
            }

            if (Input.GetKeyDown(KeyCode.Q))
            {
                if (characterAnimator.GetBool("walking") == true)
                {
                    characterAnimator.SetBool("walking", false);
                    characterAnimator.SetInteger("condition", 0);
                }
                else if (characterAnimator.GetBool("running") == true)
                {
                    characterAnimator.SetBool("running", false);
                    characterAnimator.SetInteger("condition", 0);
                }
                if (characterAnimator.GetBool("walking") == false && characterAnimator.GetBool("running") == false)
                {
                    Kicking();
                }
            }

            if (Input.GetKeyDown(KeyCode.E))
            {
                if (characterAnimator.GetBool("walking") == true)
                {
                    characterAnimator.SetBool("walking", false);
                    characterAnimator.SetInteger("condition", 0);
                }
                else if (characterAnimator.GetBool("running") == true)
                {
                    characterAnimator.SetBool("running", false);
                    characterAnimator.SetInteger("condition", 0);
                }
                if (characterAnimator.GetBool("walking") == false && characterAnimator.GetBool("running") == false)
                {
                    Taunting();
                }
            }
        }
    }

    void Attacking()
    {
        StartCoroutine(AttackRoutine());
    }

    IEnumerator AttackRoutine()
    {
        characterAnimator.SetBool("attacking", true);
        characterAnimator.SetInteger("condition", 2);
        yield return new WaitForSeconds(3);
        characterAnimator.SetInteger("condition", 0);
        characterAnimator.SetBool("attacking", false);
    }

    void Kicking()
    {
        StartCoroutine(KickRoutine());
    }

    IEnumerator KickRoutine()
    {
        characterAnimator.SetBool("kicking", true);
        characterAnimator.SetInteger("condition", 3);
        yield return new WaitForSeconds(4);
        characterAnimator.SetInteger("condition", 0);
        characterAnimator.SetBool("kicking", false);
    }

    void Taunting()
    {
        StartCoroutine(TauntRoutine());
    }

    IEnumerator TauntRoutine()
    {
        characterAnimator.SetBool("taunting", true);
        characterAnimator.SetInteger("condition", 5);
        voice.Play();
        yield return new WaitForSeconds(1);
        characterAnimator.SetInteger("condition", 0);
        characterAnimator.SetBool("taunting", false);
    }
}
