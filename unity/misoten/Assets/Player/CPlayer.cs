using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayer : MonoBehaviour {
    public float speed = 3.0F;
    public float runspeed = 5.0F;
    public float rotateSpeed = 3.0F;
    Animator animator;
    CharacterController controller;

    void Start() {
        controller = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
    }

    void Update() {
        // 左右キー Yを軸として回転
        transform.Rotate(0, Input.GetAxis("Horizontal") * rotateSpeed, 0);

        // 上下キー 前後移動
        Vector3 forward = transform.TransformDirection(Vector3.forward);
        float curSpeed = speed * Input.GetAxis("Vertical");
        if (Input.GetKey(KeyCode.LeftShift)) {
            curSpeed = runspeed * Input.GetAxis("Vertical");
        }
        controller.SimpleMove(forward * curSpeed);

        if(curSpeed > speed) {
            animator.SetBool("run", true);
        }
        else {
            animator.SetBool("run", false);
        }
        
        if(curSpeed > 0.1f) {
            animator.SetBool("walk", true);
        }
        else {
            animator.SetBool("walk", false);
        }

        if(curSpeed < -0.1f) {
            animator.SetBool("back", true);
        }
        else {
            animator.SetBool("back", false);
        }
    }
}