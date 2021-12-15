using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotation : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        transform.LookAt(new Vector3(0, transform.position.y, 0));
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
