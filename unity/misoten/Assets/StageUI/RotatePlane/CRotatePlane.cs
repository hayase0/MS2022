using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CRotatePlane : MonoBehaviour {

    [SerializeField] private Vector3 center = Vector3.zero;
    [SerializeField] private Vector3 axis = Vector3.up;
    [SerializeField] private float period = 1.0f;
    [SerializeField] private float spd = 0.0f;
    [SerializeField] private float spd_low = 0.05f;
    [SerializeField] private float spd_high = 2.0f;
    [SerializeField] private float acceleration = 1.25f;
    [SerializeField] private float decelerate = 1.5f;
    [SerializeField] private int cnt = 0;
    [SerializeField] private int cnt_point = 1;
    [SerializeField] private GameObject spdChanger;

    [SerializeField] private bool on_accele = false;

    private void Start() {
        spd = spd_low;
    }


    void Update() {

        transform.RotateAround(
            center,
            axis,
            360 / period * Time.deltaTime * spd);

        if (on_accele) {
            spd *= acceleration;

            if (spd >= spd_high) {
                spd = spd_high;
            }
        }
        else {
            spd /= decelerate;

            if (spd <= spd_low) {
                spd = spd_low;
            }
        }

    }

    private void OnTriggerEnter(Collider collision) {
        if (collision.gameObject == spdChanger) {
            if (cnt == cnt_point) {
                on_accele = true;
            }
            if (cnt > cnt_point) {
                on_accele = false;
                cnt = 0;
            }
            cnt++;
        }
    }
}
