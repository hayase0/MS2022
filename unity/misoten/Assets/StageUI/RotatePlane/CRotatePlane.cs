using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CRotatePlane : MonoBehaviour {

    [SerializeField] private Vector3 center = Vector3.zero;
    [SerializeField] private Vector3 axis = Vector3.up;
    [SerializeField] private float period = 2;
    private float spd = 0.3f;

    private int cnt = 0;
    [SerializeField] private GameObject spdChanger;

    void Update() {

        transform.RotateAround(
            center,
            axis,
            360 / period * Time.deltaTime * spd);
        
    }

    private void OnCollisionExit(Collision collision) {
        if (collision.gameObject == spdChanger) {
            if (cnt > 3 && spd == 0.3f)  {
                spd = 1.0f;
                cnt = 0;
            }else if (cnt > 1 && spd == 1.0f) {
                spd = 0.3f;
                cnt = 0;
            }
            
            cnt++;
        }
    }
}
