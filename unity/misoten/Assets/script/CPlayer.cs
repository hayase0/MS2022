using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CPlayer : MonoBehaviour {
    [SerializeField] private float moveSpeed;
    [SerializeField] private float rotateSpeed;


    private void Start() {

    }

    private void Update() {
        float inputX = Input.GetAxis("Horizontal");
        float inputZ = Input.GetAxis("Vertical");
        float rotateY = inputX * rotateSpeed * Time.deltaTime;
        float moveZ = inputZ * moveSpeed * Time.deltaTime;


        transform.Translate(0.0f, 0.0f, moveZ);

        transform.Rotate(0.0f, rotateY, 0.0f);
    }
}